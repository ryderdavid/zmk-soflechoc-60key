/*
 * Copyright (c) 2026 ryderdavid
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>

/* nice!view canvas constants (CANVAS_SIZE, CANVAS_BUF_SIZE, etc.) */
#include "widgets/util.h"

/**
 * Widget that shows currently held modifier keys as Mac symbols
 * (⇧=Shift, ⌃=Ctrl, ⌥=Alt, ⌘=Cmd) drawn on a rotated canvas that
 * overlays the BT-profile section of the nice!view status screen.
 * The canvas is hidden when no modifiers are held.
 */
struct zmk_widget_mod_status {
    sys_snode_t node;
    lv_obj_t *canvas;
    uint8_t cbuf[CANVAS_BUF_SIZE];
};

int zmk_widget_mod_status_init(struct zmk_widget_mod_status *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_mod_status_obj(struct zmk_widget_mod_status *widget);
