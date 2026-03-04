/*******************************************************************************
 * Size: 22 px
 * Bpp: 1
 * Opts: --font /System/Library/Fonts/SFCompact.ttf --bpp 1 --size 22 --range 0x20,0x21E7,0x21EA,0x2303,0x2325,0x2318 --format lvgl --output mac_symbols_22.c --lv-include lvgl.h --no-compress
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef MAC_SYMBOLS_22
#define MAC_SYMBOLS_22 1
#endif

#if MAC_SYMBOLS_22

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+21E7 "⇧" */
    0x0, 0xc0, 0x0, 0x78, 0x0, 0x3f, 0x0, 0x1f,
    0xe0, 0xf, 0x3c, 0x7, 0x87, 0x83, 0xc0, 0xf1,
    0xe0, 0x1e, 0xfe, 0x1f, 0xff, 0x87, 0xf7, 0xe1,
    0xf8, 0x38, 0x70, 0xe, 0x1c, 0x3, 0xff, 0x0,
    0xff, 0xc0, 0x1f, 0xe0,

    /* U+21EA "⇪" */
    0x0, 0xe0, 0x0, 0x3e, 0x0, 0x1f, 0xf0, 0x7,
    0x8f, 0x1, 0xe0, 0xf0, 0x78, 0xf, 0x1f, 0x83,
    0xf7, 0xf0, 0x7f, 0x7e, 0xf, 0xc1, 0xff, 0xc0,
    0x3f, 0xf8, 0x0, 0x0, 0x0, 0x7f, 0xc0, 0x1f,
    0xfc, 0x3, 0x83, 0x80, 0x7f, 0xf0, 0x7, 0xfc,
    0x0,

    /* U+2303 "⌃" */
    0x3, 0x80, 0xf, 0x80, 0x3f, 0x80, 0xff, 0x83,
    0xef, 0x8f, 0x8f, 0xbf, 0x1f, 0xfc, 0x1f, 0xf0,
    0x1e, 0xc0, 0x18,

    /* U+2318 "⌘" */
    0x38, 0x1c, 0xfc, 0x3f, 0xee, 0x77, 0xee, 0x77,
    0xff, 0xff, 0x3f, 0xfc, 0xe, 0x70, 0xe, 0x70,
    0xe, 0x70, 0x3f, 0xfc, 0xff, 0xff, 0xee, 0x77,
    0xee, 0x77, 0xfc, 0x3f, 0x38, 0x1c,

    /* U+2325 "⌥" */
    0x7e, 0x3f, 0xff, 0xcf, 0xf7, 0xfb, 0xfc, 0xe,
    0x0, 0x3, 0xc0, 0x0, 0xf0, 0x0, 0x1e, 0x0,
    0x7, 0x80, 0x0, 0xf0, 0x0, 0x3c, 0x0, 0x7,
    0x0, 0x1, 0xe0, 0x0, 0x3f, 0xc0, 0xf, 0xf0,
    0x1, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 76, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 350, .box_w = 18, .box_h = 16, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 37, .adv_w = 341, .box_w = 19, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 312, .box_w = 15, .box_h = 10, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 97, .adv_w = 318, .box_w = 16, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 340, .box_w = 18, .box_h = 15, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x21c7, 0x21ca, 0x22e3, 0x22f8, 0x2305
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 8966, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 6, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
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

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t mac_symbols_22 = {
#else
lv_font_t mac_symbols_22 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if MAC_SYMBOLS_22*/

