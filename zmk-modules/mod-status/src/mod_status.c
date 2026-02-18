/*
 * Copyright (c) 2026 ryderdavid
 * SPDX-License-Identifier: MIT
 *
 * nice!view modifier-key indicator widget.
 *
 * Subscribes to zmk_keycode_state_changed events.  On every event it
 * reads zmk_hid_get_explicit_mods() and updates a small LVGL label
 * that sits over the middle section of the nice!view status screen.
 *
 * Active modifiers are shown as single-letter abbreviations:
 *   S = Shift   C = Ctrl   A = Alt/Opt   G = GUI/Cmd
 *
 * The label is hidden (zero-sized, transparent) when no modifiers are
 * held, so the existing display content shows through untouched.
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
    char text[16] = {};

    /* Build indicator string — only active modifiers, SCAG order */
    if (state.mods & (MOD_LSFT | MOD_RSFT)) {
        strcat(text, "S ");
    }
    if (state.mods & (MOD_LCTL | MOD_RCTL)) {
        strcat(text, "C ");
    }
    if (state.mods & (MOD_LALT | MOD_RALT)) {
        strcat(text, "A ");
    }
    if (state.mods & (MOD_LGUI | MOD_RGUI)) {
        strcat(text, "G ");
    }

    /* Trim trailing space */
    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == ' ') {
        text[len - 1] = '\0';
    }

    lv_label_set_text(widget->label, text);

    if (state.mods) {
        lv_obj_remove_flag(widget->label, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(widget->label, LV_OBJ_FLAG_HIDDEN);
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
    widget->label = lv_label_create(parent);

    /* Font: same size as the layer-name text */
    lv_obj_set_style_text_font(widget->label, &lv_font_montserrat_14,
                               LV_PART_MAIN | LV_STATE_DEFAULT);

    /* Opaque background so the label is readable over the BT-circle canvas */
    lv_obj_set_style_bg_opa(widget->label, LV_OPA_COVER,
                            LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(widget->label, LVGL_BACKGROUND,
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(widget->label, LVGL_FOREGROUND,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

    /* Position over the centre of the BT-profile section (x=24..92, y=0..68) */
    lv_obj_set_pos(widget->label, 30, 26);

    /* Add a 2px padding so the background rectangle has breathing room */
    lv_obj_set_style_pad_all(widget->label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    /* Start hidden — content is empty until a modifier is pressed */
    lv_label_set_text(widget->label, "");
    lv_obj_add_flag(widget->label, LV_OBJ_FLAG_HIDDEN);

    sys_slist_append(&widgets, &widget->node);

    /* Prime the state so the widget reflects any mods held at boot */
    widget_mod_status_init();

    return 0;
}

lv_obj_t *zmk_widget_mod_status_obj(struct zmk_widget_mod_status *widget) {
    return widget->label;
}
