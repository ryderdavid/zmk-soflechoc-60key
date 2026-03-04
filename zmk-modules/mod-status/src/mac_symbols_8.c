/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Glyphs: ⌃ (U+2303) ⌘ (U+2318) ⌥ (U+2325)
 * Hand-drawn 1-bpp bitmaps for stacked modifier display in the ticker.
 * LVGL 1bpp uses continuous bit packing (no byte-per-row alignment).
 ******************************************************************************/

#include "lvgl.h"

#ifndef MAC_SYMBOLS_8
#define MAC_SYMBOLS_8 1
#endif

#if MAC_SYMBOLS_8

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x00,

    /* U+2303 "⌃"  7w × 4h  upward chevron (continuous packing, 28 bits = 4 bytes)
     *    ...X...
     *    ..X.X..
     *    .X...X.
     *    X.....X
     */
    0x10, 0x51, 0x14, 0x10,

    /* U+2318 "⌘"  5w × 5h  looped square (continuous packing, 25 bits = 4 bytes)
     *    .X.X.
     *    X.X.X
     *    .XXX.
     *    X.X.X
     *    .X.X.
     */
    0x55, 0x5d, 0x55, 0x00,

    /* U+2325 "⌥"  7w × 5h  option fork (continuous packing, 35 bits = 5 bytes)
     *    ....XXX
     *    ...X...
     *    ..X....
     *    .X.....
     *    XXX....
     */
    0x0e, 0x20, 0x82, 0x0e, 0x00
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0,   .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0}, /* id 0 reserved */
    {.bitmap_index = 0, .adv_w = 32,  .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0}, /* space */
    {.bitmap_index = 1, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 2}, /* ⌃ */
    {.bitmap_index = 5, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1}, /* ⌘ */
    {.bitmap_index = 9, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 1}, /* ⌥ */
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x22e3, 0x22f8, 0x2305
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 8966, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL,
        .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

#if LVGL_VERSION_MAJOR >= 8
const lv_font_t mac_symbols_8 = {
#else
lv_font_t mac_symbols_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 8,
    .base_line = 0,
    .subpx = LV_FONT_SUBPX_NONE,
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = (const void *)&font_dsc,
    .fallback = NULL,
    .user_data = NULL
};

#endif /* MAC_SYMBOLS_8 */
