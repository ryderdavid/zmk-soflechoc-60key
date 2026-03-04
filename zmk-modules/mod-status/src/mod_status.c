/*
 * Copyright (c) 2026 ryderdavid
 * SPDX-License-Identifier: MIT
 *
 * nice!view modifier-key indicator widget.
 *
 * Shows modifier glyphs when modifiers are held.
 * Mac mode: ⇧⌃⌥⌘ symbols.  Windows mode (layers 10-12): ⇧ CTL ALT ⊞.
 * Caps toggle indicator is handled by the layer name in status.c
 * (lowercase → UPPERCASE when CAPS_DISPLAY layer is active).
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
#include <zmk/events/layer_state_changed.h>
#include <zmk/hid.h>
#include <zmk/keymap.h>
#include <dt-bindings/zmk/modifiers.h>

/* Windows-mode layers (from sofle.keymap) */
#define WINMODE_LAYER_IDX   10
#define WINGAL_LAYER_IDX    11
#define WINMSE_LAYER_IDX    12

/* util.h from the nice!view widget directory (included via CMakeLists) */
#include "util.h"

#include "mod_status.h"

/* Custom 1-bpp fonts: ⇧ ⌃ ⌥ ⌘ at four sizes for 1/2/3/4 mod layout */
LV_FONT_DECLARE(mac_symbols_14);
LV_FONT_DECLARE(mac_symbols_22);
LV_FONT_DECLARE(mac_symbols_32);
LV_FONT_DECLARE(mac_symbols_48);

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

#define MOD_CANVAS_W 68

/* Single-symbol UTF-8 (SCAG order): ⇧ ⌃ ⌥ ⌘ */
static const char mod_sym_shift[] = "\xe2\x87\xa7";
static const char mod_sym_ctrl[]  = "\xe2\x8c\x83";
static const char mod_sym_alt[]   = "\xe2\x8c\xa5";
static const char mod_sym_gui[]   = "\xe2\x8c\x98";

/* Per-cell rectangles (x, y, width): each glyph is drawn centered in its cell. */
static const int16_t layout_x[4][4] = {
    { 0 },                     /* 1 mod: full canvas */
    { 0, 34 },                 /* 2 mods: top-left quad, bottom-right quad */
    { 0, 23, 46 },             /* 3 mods: diagonal cells */
    { 0, 34, 0, 34 },          /* 4 mods: 2×2 quadrants */
};
static const int16_t layout_y[4][4] = {
    { 0 },
    { 0, 34 },
    { 0, 23, 46 },
    { 0, 0, 34, 34 },
};
static const int16_t layout_w[4][4] = {
    { 68 },
    { 34, 34 },
    { 23, 22, 22 },
    { 34, 34, 34, 34 },
};

/* ------------------------------------------------------------------ */
/* State                                                               */
/* ------------------------------------------------------------------ */

struct mod_status_state {
    uint8_t mods;        /* zmk_mod_flags_t bitmask */
    bool windows_mode;   /* true when any WINMODE layer is active */
};

/* ------------------------------------------------------------------ */
/* Display update (runs in the LVGL work-queue context)               */
/* ------------------------------------------------------------------ */

/* Glyph rendering types for per-modifier drawing */
enum glyph_type {
    GLYPH_SYMBOL,   /* Mac symbol via mac_symbols font */
    GLYPH_TEXT,      /* Text label via Montserrat font */
    GLYPH_WINLOGO,   /* Windows logo drawn programmatically */
};

struct glyph_entry {
    enum glyph_type type;
    const char *text;  /* symbol UTF-8 or text label (NULL for WINLOGO) */
};

/* Draw a Windows logo (2×2 grid of filled squares) centered in a cell */
static void draw_win_logo(lv_obj_t *canvas, int16_t cx, int16_t cy,
                           int16_t cw, int16_t ch) {
    /* Logo occupies ~60% of the cell */
    int16_t logo_size;
    int16_t gap;

    if (cw >= 60) {
        logo_size = 40; gap = 4;
    } else if (cw >= 30) {
        logo_size = 20; gap = 2;
    } else {
        logo_size = 13; gap = 1;
    }

    int16_t pane = (logo_size - gap) / 2;
    int16_t ox = cx + (cw - logo_size) / 2;
    int16_t oy = cy + (ch - logo_size) / 2;

    lv_draw_rect_dsc_t rect_dsc;
    init_rect_dsc(&rect_dsc, LVGL_FOREGROUND);

    /* Top-left */
    canvas_draw_rect(canvas, ox, oy, pane, pane, &rect_dsc);
    /* Top-right */
    canvas_draw_rect(canvas, ox + pane + gap, oy, pane, pane, &rect_dsc);
    /* Bottom-left */
    canvas_draw_rect(canvas, ox, oy + pane + gap, pane, pane, &rect_dsc);
    /* Bottom-right */
    canvas_draw_rect(canvas, ox + pane + gap, oy + pane + gap, pane, pane, &rect_dsc);
}

static void set_mod_status(struct zmk_widget_mod_status *widget,
                           struct mod_status_state state) {
    /* Build list of active glyphs in SCAG order (max 4) */
    struct glyph_entry entries[4];
    int n = 0;

    if (state.mods & (MOD_LSFT | MOD_RSFT)) {
        /* Shift symbol is universal */
        entries[n++] = (struct glyph_entry){GLYPH_SYMBOL, mod_sym_shift};
    }
    if (state.mods & (MOD_LCTL | MOD_RCTL)) {
        entries[n++] = state.windows_mode
            ? (struct glyph_entry){GLYPH_TEXT, "CTL"}
            : (struct glyph_entry){GLYPH_SYMBOL, mod_sym_ctrl};
    }
    if (state.mods & (MOD_LALT | MOD_RALT)) {
        entries[n++] = state.windows_mode
            ? (struct glyph_entry){GLYPH_TEXT, "ALT"}
            : (struct glyph_entry){GLYPH_SYMBOL, mod_sym_alt};
    }
    if (state.mods & (MOD_LGUI | MOD_RGUI)) {
        entries[n++] = state.windows_mode
            ? (struct glyph_entry){GLYPH_WINLOGO, NULL}
            : (struct glyph_entry){GLYPH_SYMBOL, mod_sym_gui};
    }

    if (n == 0) {
        lv_obj_add_flag(widget->canvas, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    /* Choose fonts by count */
    const lv_font_t *sym_font;
    const lv_font_t *txt_font;
    int idx = n - 1;
    switch (n) {
        case 1:
            sym_font = &mac_symbols_48;
            txt_font = &lv_font_montserrat_18;
            break;
        case 2:
            sym_font = &mac_symbols_32;
            txt_font = &lv_font_montserrat_16;
            break;
        default: /* 3 or 4 */
            sym_font = &mac_symbols_22;
            txt_font = &lv_font_montserrat_14;
            break;
    }

    lv_canvas_fill_bg(widget->canvas, LVGL_BACKGROUND, LV_OPA_COVER);

    for (int i = 0; i < n; i++) {
        int16_t cx = layout_x[idx][i];
        int16_t cy = layout_y[idx][i];
        int16_t cw = layout_w[idx][i];
        int16_t ch = cw; /* cells are square */

        switch (entries[i].type) {
        case GLYPH_SYMBOL: {
            lv_draw_label_dsc_t label_dsc;
            init_label_dsc(&label_dsc, LVGL_FOREGROUND, sym_font, LV_TEXT_ALIGN_CENTER);
            if (n == 1) {
                cy = (MOD_CANVAS_W - (int16_t)sym_font->line_height) / 2;
            }
            canvas_draw_text(widget->canvas, cx, cy, cw, &label_dsc, entries[i].text);
            break;
        }
        case GLYPH_TEXT: {
            lv_draw_label_dsc_t label_dsc;
            init_label_dsc(&label_dsc, LVGL_FOREGROUND, txt_font, LV_TEXT_ALIGN_CENTER);
            /* Center text vertically in cell */
            int16_t text_y = cy + (ch - (int16_t)txt_font->line_height) / 2;
            if (n == 1) {
                text_y = (MOD_CANVAS_W - (int16_t)txt_font->line_height) / 2;
            }
            canvas_draw_text(widget->canvas, cx, text_y, cw, &label_dsc, entries[i].text);
            break;
        }
        case GLYPH_WINLOGO: {
            if (n == 1) {
                cy = 0;
                ch = MOD_CANVAS_W;
            }
            draw_win_logo(widget->canvas, cx, cy, cw, ch);
            break;
        }
        }
    }

    rotate_canvas(widget->canvas);
    lv_obj_remove_flag(widget->canvas, LV_OBJ_FLAG_HIDDEN);
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
    return (struct mod_status_state){
        .mods = zmk_hid_get_explicit_mods(),
        .windows_mode = zmk_keymap_layer_active(WINMODE_LAYER_IDX) ||
                        zmk_keymap_layer_active(WINGAL_LAYER_IDX) ||
                        zmk_keymap_layer_active(WINMSE_LAYER_IDX),
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_mod_status, struct mod_status_state,
                             mod_status_update_cb, mod_status_get_state)

ZMK_SUBSCRIPTION(widget_mod_status, zmk_keycode_state_changed);
ZMK_SUBSCRIPTION(widget_mod_status, zmk_layer_state_changed);

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
