/*
 * Copyright (c) 2026 ryderdavid
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>

/* Mirror the nice!view canvas constants without including util.h
 * (which has no include guards and would cause struct redefinition
 * when both status.h and mod_status.h are included). */
#define MOD_CANVAS_SIZE 68
#define MOD_CANVAS_COLOR_FORMAT LV_COLOR_FORMAT_L8
#define MOD_CANVAS_BUF_SIZE                                                    \
    LV_CANVAS_BUF_SIZE(MOD_CANVAS_SIZE, MOD_CANVAS_SIZE,                       \
                       LV_COLOR_FORMAT_GET_BPP(MOD_CANVAS_COLOR_FORMAT),       \
                       LV_DRAW_BUF_STRIDE_ALIGN)

/**
 * Widget that shows currently held modifier keys as Mac symbols
 * (⇧=Shift, ⌃=Ctrl, ⌥=Alt, ⌘=Cmd) drawn on a rotated canvas that
 * overlays the BT-profile section of the nice!view status screen.
 * The canvas is hidden when no modifiers are held.
 */
struct zmk_widget_mod_status {
    sys_snode_t node;
    lv_obj_t *canvas;
    uint8_t cbuf[MOD_CANVAS_BUF_SIZE];
};

int zmk_widget_mod_status_init(struct zmk_widget_mod_status *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_mod_status_obj(struct zmk_widget_mod_status *widget);
