/*
 *
 * Copyright (c) 2025 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 *
 */

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/battery.h>
#include <zmk/display.h>
#include "status.h"
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/wpm_state_changed.h>
#include <zmk/events/layer_state_changed.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/events/position_state_changed.h>
#include <zmk/usb.h>
#include <dt-bindings/zmk/modifiers.h>
#include <dt-bindings/zmk/hid_usage.h>
#include <dt-bindings/zmk/hid_usage_pages.h>
#include <string.h>
#include <zmk/ble.h>
#include <zmk/endpoints.h>
#include <zmk/keymap.h>
#include <zmk/wpm.h>
#include <zmk/hid.h>

LV_FONT_DECLARE(mac_symbols_8);

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct output_status_state {
    struct zmk_endpoint_instance selected_endpoint;
    int active_profile_index;
    bool active_profile_connected;
    bool active_profile_bonded;
    bool profiles_connected[NICEVIEW_PROFILE_COUNT];
    bool profiles_bonded[NICEVIEW_PROFILE_COUNT];
};

struct layer_status_state {
    zmk_keymap_layer_index_t index;
    const char *label;
};

struct wpm_status_state {
    uint8_t wpm;
};

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
/* US QWERTY: map HID keyboard keycode + shift to printable char. Returns 0 if non-printable. */
static char keycode_to_char(uint16_t usage_page, uint32_t keycode, uint8_t mods) {
    if (usage_page != HID_USAGE_KEY) {
        return 0;
    }
    switch (keycode) {
    case 0x28: return '\x01'; /* Enter */
    case 0x2A: return '\x02'; /* Backspace */
    case 0x2B: return '\x03'; /* Tab */
    case 0x4C: return '\x04'; /* Delete (forward) */
    }
    if (keycode < 0x04 || keycode > 0x38) {
        return 0;
    }
    bool shift = (mods & (MOD_LSFT | MOD_RSFT)) != 0;
    /* 0x04..0x1D a-z, 0x1E..0x27 1-0, 0x28..0x2B non-print, 0x2C space, 0x2D..0x38 -_=[]\`;'`,./ */
    static const char unshifted[54] = {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '1','2','3','4','5','6','7','8','9','0',
        0, 0, 0, 0, ' ', '-', '=', '[', ']', '\\', 0, ';', '\'', '`', ',', '.', '/', 0
    };
    static const char shifted[54] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        '!','@','#','$','%','^','&','*','(',')',
        0, 0, 0, 0, ' ', '_', '+', '{', '}', '|', '~', ':', '"', '~', '<', '>', '?', 0
    };
    unsigned idx = keycode - 0x04;
    if (idx >= 54) {
        return 0;
    }
    char c = shift ? shifted[idx] : unshifted[idx];
    return (c >= 0x20 && c < 0x7F) ? c : 0;
}

/* Store oldest at [0], newest at [3] so the string reads in typing order.
 * mod_byte carries Ctrl/Alt/Cmd bits (Shift already reflected in char). */
static void ticker_push_char_mod(struct zmk_widget_status *widget, char c, uint8_t mod_byte) {
    if (c == 0) {
        return;
    }
    char *t = widget->state.ticker_chars;
    uint8_t *m = widget->state.ticker_mods;
    uint8_t *len = &widget->state.ticker_len;
    if (*len < 4) {
        t[*len] = c;
        m[*len] = mod_byte;
        *len += 1;
    } else {
        t[0] = t[1]; t[1] = t[2]; t[2] = t[3]; t[3] = c;
        m[0] = m[1]; m[1] = m[2]; m[2] = m[3]; m[3] = mod_byte;
    }
    t[*len] = '\0';
}

static void ticker_update_position(struct zmk_widget_status *widget, uint32_t position) {
    widget->state.ticker_position = position;
}
#endif

static void draw_top(lv_obj_t *widget, const struct status_state *state) {
    lv_obj_t *canvas = lv_obj_get_child(widget, 0);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_16, LV_TEXT_ALIGN_RIGHT);
    lv_draw_label_dsc_t label_dsc_wpm;
    init_label_dsc(&label_dsc_wpm, LVGL_FOREGROUND, &lv_font_unscii_8, LV_TEXT_ALIGN_RIGHT);
    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);
    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);
    lv_draw_line_dsc_t line_dsc;
    init_line_dsc(&line_dsc, LVGL_FOREGROUND, 1);

    // Fill background
    lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);

    // Draw battery
    draw_battery(canvas, state);

    // Draw output status
    char output_text[10] = {};

    switch (state->selected_endpoint.transport) {
    case ZMK_TRANSPORT_USB:
        strcat(output_text, LV_SYMBOL_USB);
        break;
    case ZMK_TRANSPORT_BLE:
        if (state->active_profile_bonded) {
            if (state->active_profile_connected) {
                strcat(output_text, LV_SYMBOL_WIFI);
            } else {
                strcat(output_text, LV_SYMBOL_CLOSE);
            }
        } else {
            strcat(output_text, LV_SYMBOL_SETTINGS);
        }
        break;
    }

    canvas_draw_text(canvas, 0, 0, CANVAS_SIZE, &label_dsc, output_text);

    // Draw WPM
    canvas_draw_rect(canvas, 0, 21, 68, 42, &rect_white_dsc);
    canvas_draw_rect(canvas, 1, 22, 66, 40, &rect_black_dsc);

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    /* Position code: top-right inside the WPM graph */
    char pos_text[6];
    snprintf(pos_text, sizeof(pos_text), "%02u", (unsigned)state->ticker_position % 100);
    lv_draw_label_dsc_t label_dsc_pos;
    init_label_dsc(&label_dsc_pos, LVGL_FOREGROUND, &lv_font_unscii_8, LV_TEXT_ALIGN_RIGHT);
    canvas_draw_text(canvas, 50, 24, 16, &label_dsc_pos, pos_text);
#endif

    int max = 0;
    int min = 256;

    for (int i = 0; i < 10; i++) {
        if (state->wpm[i] > max) {
            max = state->wpm[i];
        }
        if (state->wpm[i] < min) {
            min = state->wpm[i];
        }
    }

    int range = max - min;
    if (range == 0) {
        range = 1;
    }

    lv_point_t points[10];
    for (int i = 0; i < 10; i++) {
        points[i].x = 2 + i * 7;
        points[i].y = 60 - (state->wpm[i] - min) * 36 / range;
    }
    canvas_draw_line(canvas, points, 10, &line_dsc);

    /* Draw WPM text and ticker AFTER the sparkline so backgrounds cover the graph */
    char wpm_text[6] = {};
    snprintf(wpm_text, sizeof(wpm_text), "%d", state->wpm[9]);
    canvas_draw_rect(canvas, 42, 52, 24, 8, &rect_black_dsc);
    canvas_draw_text(canvas, 42, 52, 24, &label_dsc_wpm, wpm_text);

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    /* Ticker: 4 vertical cells with modifier icons stacked bottom-up above each char.
     * Each element gets a black background rect to block the WPM line graph. */
    if (state->ticker_len > 0) {
        static const char sym_ctrl[] = "\xe2\x8c\x83";
        static const char sym_alt[]  = "\xe2\x8c\xa5";
        static const char sym_gui[]  = "\xe2\x8c\x98";

        lv_draw_label_dsc_t label_dsc_tchar;
        init_label_dsc(&label_dsc_tchar, LVGL_FOREGROUND, &lv_font_unscii_8, LV_TEXT_ALIGN_CENTER);
        lv_draw_label_dsc_t label_dsc_tmod;
        init_label_dsc(&label_dsc_tmod, LVGL_FOREGROUND, &mac_symbols_8, LV_TEXT_ALIGN_CENTER);

        for (int i = 0; i < state->ticker_len; i++) {
            int16_t cx = 2 + i * 10;

            canvas_draw_rect(canvas, cx, 52, 9, 8, &rect_black_dsc);
            char ch_val = state->ticker_chars[i];
            if (ch_val >= 0x20) {
                char ch[2] = { ch_val, '\0' };
                canvas_draw_text(canvas, cx, 52, 9, &label_dsc_tchar, ch);
            } else {
                canvas_draw_rect(canvas, cx + 3, 54, 3, 3, &rect_white_dsc);
            }

            uint8_t mod = state->ticker_mods[i];
            int slot = 0;
            if (mod & (MOD_LCTL | MOD_RCTL)) {
                int16_t my = 44 - slot * 8;
                canvas_draw_rect(canvas, cx, my, 9, 8, &rect_black_dsc);
                canvas_draw_text(canvas, cx, my, 9, &label_dsc_tmod, sym_ctrl);
                slot++;
            }
            if (mod & (MOD_LALT | MOD_RALT)) {
                int16_t my = 44 - slot * 8;
                canvas_draw_rect(canvas, cx, my, 9, 8, &rect_black_dsc);
                canvas_draw_text(canvas, cx, my, 9, &label_dsc_tmod, sym_alt);
                slot++;
            }
            if (mod & (MOD_LGUI | MOD_RGUI)) {
                int16_t my = 44 - slot * 8;
                canvas_draw_rect(canvas, cx, my, 9, 8, &rect_black_dsc);
                canvas_draw_text(canvas, cx, my, 9, &label_dsc_tmod, sym_gui);
                slot++;
            }
        }
    }
#endif

    // Rotate canvas
    rotate_canvas(canvas);
}

static void draw_middle(lv_obj_t *widget, const struct status_state *state) {
    lv_obj_t *canvas = lv_obj_get_child(widget, 1);

    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);
    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);
    lv_draw_arc_dsc_t arc_dsc;
    init_arc_dsc(&arc_dsc, LVGL_FOREGROUND, 2);
    lv_draw_arc_dsc_t arc_dsc_filled;
    init_arc_dsc(&arc_dsc_filled, LVGL_FOREGROUND, 9);
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_18, LV_TEXT_ALIGN_CENTER);
    lv_draw_label_dsc_t label_dsc_black;
    init_label_dsc(&label_dsc_black, LVGL_BACKGROUND, &lv_font_montserrat_18, LV_TEXT_ALIGN_CENTER);

    // Fill background
    lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);

    // Draw circles
    int circle_offsets[NICEVIEW_PROFILE_COUNT][2] = {
        {13, 13}, {55, 13}, {34, 34}, {13, 55}, {55, 55},
    };

    for (int i = 0; i < NICEVIEW_PROFILE_COUNT; i++) {
        bool selected = i == state->active_profile_index;

        if (state->profiles_connected[i]) {
            canvas_draw_arc(canvas, circle_offsets[i][0], circle_offsets[i][1], 13, 0, 360,
                            &arc_dsc);
        } else if (state->profiles_bonded[i]) {
            const int segments = 8;
            const int gap = 20;
            for (int j = 0; j < segments; ++j)
                canvas_draw_arc(canvas, circle_offsets[i][0], circle_offsets[i][1], 13,
                                360. / segments * j + gap / 2.0,
                                360. / segments * (j + 1) - gap / 2.0, &arc_dsc);
        }

        if (selected) {
            canvas_draw_arc(canvas, circle_offsets[i][0], circle_offsets[i][1], 9, 0, 359,
                            &arc_dsc_filled);
        }

        char label[2];
        snprintf(label, sizeof(label), "%d", i + 1);
        canvas_draw_text(canvas, circle_offsets[i][0] - 8, circle_offsets[i][1] - 10, 16,
                         (selected ? &label_dsc_black : &label_dsc), label);
    }

    // Rotate canvas
    rotate_canvas(canvas);
}

static void draw_bottom(lv_obj_t *widget, const struct status_state *state) {
    lv_obj_t *canvas = lv_obj_get_child(widget, 2);

    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);
    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_14, LV_TEXT_ALIGN_CENTER);

    // Fill background
    lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);

    // Draw layer
    if (state->layer_label == NULL || strlen(state->layer_label) == 0) {
        char text[10] = {};

        sprintf(text, "LAYER %i", state->layer_index);

        canvas_draw_text(canvas, 0, 5, 68, &label_dsc, text);
    } else {
        canvas_draw_text(canvas, 0, 5, 68, &label_dsc, state->layer_label);
    }

    // Rotate canvas
    rotate_canvas(canvas);
}

static void set_battery_status(struct zmk_widget_status *widget,
                               struct battery_status_state state) {
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    widget->state.charging = state.usb_present;
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

    widget->state.battery = state.level;

    draw_top(widget->obj, &widget->state);
}

static void battery_status_update_cb(struct battery_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_battery_status(widget, state); }
}

static struct battery_status_state battery_status_get_state(const zmk_event_t *eh) {
    const struct zmk_battery_state_changed *ev = as_zmk_battery_state_changed(eh);

    return (struct battery_status_state){
        .level = (ev != NULL) ? ev->state_of_charge : zmk_battery_state_of_charge(),
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
        .usb_present = zmk_usb_is_powered(),
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_battery_status, struct battery_status_state,
                            battery_status_update_cb, battery_status_get_state)

ZMK_SUBSCRIPTION(widget_battery_status, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(widget_battery_status, zmk_usb_conn_state_changed);
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

static void set_output_status(struct zmk_widget_status *widget,
                              const struct output_status_state *state) {
    widget->state.selected_endpoint = state->selected_endpoint;
    widget->state.active_profile_index = state->active_profile_index;
    widget->state.active_profile_connected = state->active_profile_connected;
    widget->state.active_profile_bonded = state->active_profile_bonded;
    for (int i = 0; i < NICEVIEW_PROFILE_COUNT; ++i) {
        widget->state.profiles_connected[i] = state->profiles_connected[i];
        widget->state.profiles_bonded[i] = state->profiles_bonded[i];
    }

    draw_top(widget->obj, &widget->state);
    draw_middle(widget->obj, &widget->state);
}

static void output_status_update_cb(struct output_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_output_status(widget, &state); }
}

static struct output_status_state output_status_get_state(const zmk_event_t *_eh) {
    struct output_status_state state = {
        .selected_endpoint = zmk_endpoints_selected(),
        .active_profile_index = zmk_ble_active_profile_index(),
        .active_profile_connected = zmk_ble_active_profile_is_connected(),
        .active_profile_bonded = !zmk_ble_active_profile_is_open(),
    };
    for (int i = 0; i < MIN(NICEVIEW_PROFILE_COUNT, ZMK_BLE_PROFILE_COUNT); ++i) {
        state.profiles_connected[i] = zmk_ble_profile_is_connected(i);
        state.profiles_bonded[i] = !zmk_ble_profile_is_open(i);
    }
    return state;
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_output_status, struct output_status_state,
                            output_status_update_cb, output_status_get_state)
ZMK_SUBSCRIPTION(widget_output_status, zmk_endpoint_changed);

#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(widget_output_status, zmk_usb_conn_state_changed);
#endif
#if defined(CONFIG_ZMK_BLE)
ZMK_SUBSCRIPTION(widget_output_status, zmk_ble_active_profile_changed);
#endif

static void set_layer_status(struct zmk_widget_status *widget, struct layer_status_state state) {
    widget->state.layer_index = state.index;
    widget->state.layer_label = state.label;

    draw_bottom(widget->obj, &widget->state);
}

static void layer_status_update_cb(struct layer_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_layer_status(widget, state); }
}

static struct layer_status_state layer_status_get_state(const zmk_event_t *eh) {
    zmk_keymap_layer_index_t index = zmk_keymap_highest_layer_active();
    return (struct layer_status_state){
        .index = index, .label = zmk_keymap_layer_name(zmk_keymap_layer_index_to_id(index))};
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_layer_status, struct layer_status_state, layer_status_update_cb,
                            layer_status_get_state)

ZMK_SUBSCRIPTION(widget_layer_status, zmk_layer_state_changed);

static void set_wpm_status(struct zmk_widget_status *widget, struct wpm_status_state state) {
    for (int i = 0; i < 9; i++) {
        widget->state.wpm[i] = widget->state.wpm[i + 1];
    }
    widget->state.wpm[9] = state.wpm;

    draw_top(widget->obj, &widget->state);
}

static void wpm_status_update_cb(struct wpm_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_wpm_status(widget, state); }
}

struct wpm_status_state wpm_status_get_state(const zmk_event_t *eh) {
    return (struct wpm_status_state){.wpm = zmk_wpm_get_state()};
};

ZMK_DISPLAY_WIDGET_LISTENER(widget_wpm_status, struct wpm_status_state, wpm_status_update_cb,
                            wpm_status_get_state)
ZMK_SUBSCRIPTION(widget_wpm_status, zmk_wpm_state_changed);

#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
/* Defer ticker redraw to display work queue to avoid freezing when typing fast */
static void ticker_redraw_work_cb(struct k_work *work) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
        draw_top(widget->obj, &widget->state);
    }
}
K_WORK_DEFINE(ticker_redraw_work, ticker_redraw_work_cb);

static int ticker_keycode_listener(const zmk_event_t *eh) {
    const struct zmk_keycode_state_changed *ev = as_zmk_keycode_state_changed(eh);
    if (ev == NULL || !ev->state) {
        return 0; /* only on key press */
    }
    uint8_t mods = zmk_hid_get_explicit_mods() | ev->implicit_modifiers;
    char c = keycode_to_char(ev->usage_page, ev->keycode, mods);
    uint8_t mod_byte = mods & ~(MOD_LSFT | MOD_RSFT);
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
        ticker_push_char_mod(widget, c, mod_byte);
    }
    if (zmk_display_is_initialized()) {
        k_work_submit_to_queue(zmk_display_work_q(), &ticker_redraw_work);
    }
    return 0;
}

static int ticker_position_listener(const zmk_event_t *eh) {
    const struct zmk_position_state_changed *ev = as_zmk_position_state_changed(eh);
    if (ev == NULL || !ev->state) {
        return 0; /* only on key press */
    }
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
        ticker_update_position(widget, ev->position);
    }
    if (zmk_display_is_initialized()) {
        k_work_submit_to_queue(zmk_display_work_q(), &ticker_redraw_work);
    }
    return 0;
}

ZMK_LISTENER(widget_ticker_keycode, ticker_keycode_listener);
ZMK_SUBSCRIPTION(widget_ticker_keycode, zmk_keycode_state_changed);

ZMK_LISTENER(widget_ticker_position, ticker_position_listener);
ZMK_SUBSCRIPTION(widget_ticker_position, zmk_position_state_changed);
#endif

int zmk_widget_status_init(struct zmk_widget_status *widget, lv_obj_t *parent) {
#if !IS_ENABLED(CONFIG_ZMK_SPLIT) || IS_ENABLED(CONFIG_ZMK_SPLIT_ROLE_CENTRAL)
    widget->state.ticker_chars[0] = '\0';
    widget->state.ticker_len = 0;
    widget->state.ticker_position = 0;
    memset(widget->state.ticker_mods, 0, sizeof(widget->state.ticker_mods));
#endif
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 160, 68);
    lv_obj_t *top = lv_canvas_create(widget->obj);
    lv_obj_align(top, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_canvas_set_buffer(top, widget->cbuf, CANVAS_SIZE, CANVAS_SIZE, CANVAS_COLOR_FORMAT);
    lv_obj_t *middle = lv_canvas_create(widget->obj);
    lv_obj_align(middle, LV_ALIGN_TOP_LEFT, 24, 0);
    lv_canvas_set_buffer(middle, widget->cbuf2, CANVAS_SIZE, CANVAS_SIZE, CANVAS_COLOR_FORMAT);
    lv_obj_t *bottom = lv_canvas_create(widget->obj);
    lv_obj_align(bottom, LV_ALIGN_TOP_LEFT, -44, 0);
    lv_canvas_set_buffer(bottom, widget->cbuf3, CANVAS_SIZE, CANVAS_SIZE, CANVAS_COLOR_FORMAT);

    sys_slist_append(&widgets, &widget->node);
    widget_battery_status_init();
    widget_output_status_init();
    widget_layer_status_init();
    widget_wpm_status_init();

    return 0;
}

lv_obj_t *zmk_widget_status_obj(struct zmk_widget_status *widget) { return widget->obj; }
