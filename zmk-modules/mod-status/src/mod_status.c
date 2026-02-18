/*
 * Copyright (c) 2026 ryderdavid
 * SPDX-License-Identifier: MIT
 *
 * nice!view modifier-key indicator widget.
 *
 * Subscribes to zmk_keycode_state_changed events.  On every event it
 * reads zmk_hid_get_explicit_mods() and draws Mac modifier symbols
 * on a rotated canvas that overlays the BT-profile section of the
 * nice!view status screen.
 *
 * Active modifiers are shown as Mac symbols (SCAG order):
 *   ⇧ = Shift   ⌃ = Ctrl   ⌥ = Alt/Opt   ⌘ = GUI/Cmd
 *
 * The canvas is hidden when no modifiers are held, so the BT-profile
 * circles show through untouched.
 *
 * Architecture note: this widget compiles ONLY on the central half
 * (left, the host-connected side).  The central is the only place where
 * zmk_hid_get_explicit_mods() is meaningful and where
 * zmk_keycode_state_changed fires after hold-tap resolution.
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <lvgl.h>

#include <zmk/display.h>
#include <zmk/event_manager.h>
#include <zmk/events/keycode_state_changed.h>
#include <zmk/hid.h>
#include <dt-bindings/zmk/modifiers.h>

/* util.h from the nice!view widget directory (included via CMakeLists) */
#include "widgets/util.h"

#include "mod_status.h"

/* Custom 1-bpp font containing only ⇧ ⌃ ⌥ ⌘ and space */
LV_FONT_DECLARE(mac_symbols_14);

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

/* ------------------------------------------------------------------ */
/* State                                                               */
/* ------------------------------------------------------------------ */

struct mod_status_state {
    uint8_t mods; /* zmk_mod_flags_t bitmask */
};

/* ------------------------------------------------------------------ */
/* Display update (runs in the LVGL work-queue context)               */
/* ------------------------------------------------------------------ */

static void set_mod_status(struct zmk_widget_mod_status *widget,
                           struct mod_status_state state) {
    char text[32] = {};

    /* Build indicator string — only active modifiers, SCAG order,
     * using Mac modifier symbols (UTF-8 encoded) */
    if (state.mods & (MOD_LSFT | MOD_RSFT)) {
        strcat(text, "\xe2\x87\xa7 ");  /* ⇧ U+21E7 */
    }
    if (state.mods & (MOD_LCTL | MOD_RCTL)) {
        strcat(text, "\xe2\x8c\x83 ");  /* ⌃ U+2303 */
    }
    if (state.mods & (MOD_LALT | MOD_RALT)) {
        strcat(text, "\xe2\x8c\xa5 ");  /* ⌥ U+2325 */
    }
    if (state.mods & (MOD_LGUI | MOD_RGUI)) {
        strcat(text, "\xe2\x8c\x98 ");  /* ⌘ U+2318 */
    }

    /* Trim trailing space */
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == ' ') {
        text[len - 1] = '\0';
    }

    if (state.mods) {
        /* Clear canvas with background colour (opaque overlay) */
        lv_canvas_fill_bg(widget->canvas, LVGL_BACKGROUND, LV_OPA_COVER);

        /* Draw modifier symbols centered in the 68×68 pre-rotation canvas */
        lv_draw_label_dsc_t label_dsc;
        init_label_dsc(&label_dsc, LVGL_FOREGROUND, &mac_symbols_14,
                       LV_TEXT_ALIGN_CENTER);
        canvas_draw_text(widget->canvas, 0, 29, CANVAS_SIZE, &label_dsc, text);

        /* Rotate 270° to match nice_view display orientation */
        rotate_canvas(widget->canvas);

        lv_obj_remove_flag(widget->canvas, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(widget->canvas, LV_OBJ_FLAG_HIDDEN);
    }
}

static void mod_status_update_cb(struct mod_status_state state) {
    struct zmk_widget_mod_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
        set_mod_status(widget, state);
    }
}

/* ------------------------------------------------------------------ */
/* State fetch (runs in the ZMK event-bus context)                    */
/* ------------------------------------------------------------------ */

static struct mod_status_state mod_status_get_state(const zmk_event_t *eh) {
    ARG_UNUSED(eh);
    return (struct mod_status_state){.mods = zmk_hid_get_explicit_mods()};
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_mod_status, struct mod_status_state,
                             mod_status_update_cb, mod_status_get_state)

ZMK_SUBSCRIPTION(widget_mod_status, zmk_keycode_state_changed);

/* ------------------------------------------------------------------ */
/* Public API                                                          */
/* ------------------------------------------------------------------ */

int zmk_widget_mod_status_init(struct zmk_widget_mod_status *widget,
                               lv_obj_t *parent) {
    widget->canvas = lv_canvas_create(parent);
    lv_canvas_set_buffer(widget->canvas, widget->cbuf, CANVAS_SIZE,
                         CANVAS_SIZE, CANVAS_COLOR_FORMAT);

    /* Position to overlay the BT-profile section (same offset as the
     * middle canvas in the stock nice!view status widget) */
    lv_obj_align(widget->canvas, LV_ALIGN_TOP_LEFT, 24, 0);

    /* Start hidden — shown only when a modifier is held */
    lv_canvas_fill_bg(widget->canvas, LVGL_BACKGROUND, LV_OPA_COVER);
    lv_obj_add_flag(widget->canvas, LV_OBJ_FLAG_HIDDEN);

    sys_slist_append(&widgets, &widget->node);

    /* Prime the state so the widget reflects any mods held at boot */
    widget_mod_status_init();

    return 0;
}

lv_obj_t *zmk_widget_mod_status_obj(struct zmk_widget_mod_status *widget) {
    return widget->canvas;
}
