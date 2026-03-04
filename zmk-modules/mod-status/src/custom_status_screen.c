/*
 * Copyright (c) 2026 ryderdavid
 * SPDX-License-Identifier: MIT
 *
 * Replacement for the nice!view shield's custom_status_screen.c.
 *
 * This file is compiled (and the original suppressed via Kconfig.defconfig)
 * when CONFIG_ZMK_WIDGET_MOD_STATUS=y on the central half.  It produces the
 * same output as the stock nice!view screen, plus initialises the modifier
 * indicator widget from mod_status.c.
 *
 * zmk_display_status_screen() is declared __attribute__((weak)) in ZMK's
 * display/main.c so that any shield or module can override it with a
 * non-weak definition — which is exactly what we do here.
 */

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <lvgl.h>
#include <zmk/display.h>

/* nice!view status widget (status.c / bolt.c / util.c compiled by our
   CMakeLists.txt from the shield source tree) */
#include "status.h"

/* Modifier indicator widget */
#include "mod_status.h"

static struct zmk_widget_status status_widget;
static struct zmk_widget_mod_status mod_status_widget;

lv_obj_t *zmk_display_status_screen(void) {
    lv_obj_t *screen;
    int ret;

    screen = lv_obj_create(NULL);
    lv_obj_remove_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    /* ---- Stock nice!view content ---------------------------------- */
    ret = zmk_widget_status_init(&status_widget, screen);
    if (ret < 0) {
        LOG_ERR("Failed to init nice!view status widget: %d", ret);
        return screen;
    }
    lv_obj_align(zmk_widget_status_obj(&status_widget), LV_ALIGN_TOP_LEFT,
                 0, 0);

    /* ---- Modifier indicator --------------------------------------- */
    ret = zmk_widget_mod_status_init(&mod_status_widget, screen);
    if (ret < 0) {
        LOG_ERR("Failed to init mod-status widget: %d", ret);
        return screen;
    }
    /* Widget positions itself internally; no additional alignment needed */

    return screen;
}
