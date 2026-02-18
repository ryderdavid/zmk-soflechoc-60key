/*
 * Copyright (c) 2026 ryderdavid
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>

/**
 * Widget that shows currently held modifier keys (S=Shift, C=Ctrl, A=Alt,
 * G=GUI/Cmd) as a label overlaid on the nice!view status screen.
 * The label is hidden when no modifiers are held.
 */
struct zmk_widget_mod_status {
    sys_snode_t node;
    lv_obj_t *label; /* LVGL label object rendered on the screen */
};

int zmk_widget_mod_status_init(struct zmk_widget_mod_status *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_mod_status_obj(struct zmk_widget_mod_status *widget);
