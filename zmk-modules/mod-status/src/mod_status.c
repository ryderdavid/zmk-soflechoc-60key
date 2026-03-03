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
    uint8_t mods; /* zmk_mod_flags_t bitmask */
};

/* ------------------------------------------------------------------ */
/* Display update (runs in the LVGL work-queue context)               */
/* ------------------------------------------------------------------ */

static void set_mod_status(struct zmk_widget_mod_status *widget,
                           struct mod_status_state state) {
    /* Build list of active symbols in SCAG order (max 4) */
    const char *symbols[4];
    int n = 0;
    if (state.mods & (MOD_LSFT | MOD_RSFT)) symbols[n++] = mod_sym_shift;
    if (state.mods & (MOD_LCTL | MOD_RCTL)) symbols[n++] = mod_sym_ctrl;
    if (state.mods & (MOD_LALT | MOD_RALT)) symbols[n++] = mod_sym_alt;
    if (state.mods & (MOD_LGUI | MOD_RGUI)) symbols[n++] = mod_sym_gui;

    if (n == 0) {
        lv_obj_add_flag(widget->canvas, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    /* Choose font by count: 1=largest/centered, 2–4=smaller dice layout; 4 mods use 22px for legibility */
    const lv_font_t *font;
    int idx = n - 1;
    switch (n) {
        case 1: font = &mac_symbols_48; break;
        case 2: font = &mac_symbols_32; break;
        case 3: font = &mac_symbols_22; break;
        default: font = &mac_symbols_22; break;  /* 4 mods: 22px (was 14) so not overly small */
    }

    lv_canvas_fill_bg(widget->canvas, LVGL_BACKGROUND, LV_OPA_COVER);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, font, LV_TEXT_ALIGN_CENTER);

    for (int i = 0; i < n; i++) {
        int16_t cx = layout_x[idx][i];
        int16_t cy = layout_y[idx][i];
        int16_t cw = layout_w[idx][i];
        /* Single mod: center the glyph vertically in the canvas; multiples use layout_y as-is */
        if (n == 1) {
            cy = (MOD_CANVAS_W - (int16_t)font->line_height) / 2;
        }
        canvas_draw_text(widget->canvas, cx, cy, cw, &label_dsc, symbols[i]);
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
