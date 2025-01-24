/*******************************************************************************
 * Size: 40 px
 * Bpp: 1
 * Opts: --bpp 1 --size 40 --no-compress --font fa-light-300.ttf --range 62767 --format lvgl -o fa_icons.c
 ******************************************************************************/

#ifndef FA_ICONS
#define FA_ICONS 1
#endif

#if FA_ICONS

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap_fa[] = {
    /* U+F52F "" */
    0x7, 0xff, 0xfe, 0x0, 0x0, 0xf, 0xff, 0xff,
    0x0, 0x0, 0x1c, 0x0, 0x3, 0x81, 0x80, 0x18,
    0x0, 0x1, 0x81, 0xc0, 0x18, 0x0, 0x1, 0x80,
    0xe0, 0x18, 0x0, 0x1, 0x80, 0x70, 0x18, 0x0,
    0x1, 0x80, 0x78, 0x18, 0x0, 0x1, 0x80, 0x7c,
    0x18, 0x0, 0x1, 0x80, 0x7e, 0x18, 0x0, 0x1,
    0x80, 0x6f, 0x18, 0x0, 0x1, 0x80, 0x67, 0x18,
    0x0, 0x1, 0x80, 0x67, 0x18, 0x0, 0x1, 0x80,
    0x67, 0x18, 0x0, 0x1, 0x80, 0x77, 0x18, 0x0,
    0x1, 0x80, 0x3f, 0x1f, 0xff, 0xff, 0x80, 0x3f,
    0x1f, 0xff, 0xff, 0x80, 0x7, 0x18, 0x0, 0x1,
    0x80, 0x7, 0x18, 0x0, 0x1, 0x80, 0x7, 0x18,
    0x0, 0x1, 0x80, 0x7, 0x18, 0x0, 0x1, 0xf8,
    0x7, 0x18, 0x0, 0x1, 0xfe, 0x7, 0x18, 0x0,
    0x1, 0x8f, 0x7, 0x18, 0x0, 0x1, 0x87, 0x7,
    0x18, 0x0, 0x1, 0x83, 0x87, 0x18, 0x0, 0x1,
    0x83, 0x87, 0x18, 0x0, 0x1, 0x83, 0x87, 0x18,
    0x0, 0x1, 0x83, 0x87, 0x18, 0x0, 0x1, 0x83,
    0x87, 0x18, 0x0, 0x1, 0x83, 0x87, 0x18, 0x0,
    0x1, 0x83, 0x87, 0x18, 0x0, 0x1, 0x83, 0x87,
    0x18, 0x0, 0x1, 0x81, 0xfe, 0x18, 0x0, 0x1,
    0x80, 0xfc, 0x18, 0x0, 0x1, 0x80, 0x30, 0x18,
    0x0, 0x1, 0x80, 0x0, 0x18, 0x0, 0x1, 0x80,
    0x0, 0x18, 0x0, 0x1, 0x80, 0x0, 0xff, 0xff,
    0xff, 0xf0, 0x0, 0xff, 0xff, 0xff, 0xf0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc_fa[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 640, .box_w = 40, .box_h = 40, .ofs_x = 0, .ofs_y = -5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps_fa[] =
{
    {
        .range_start = 62767, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache_fa;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc_fa = {
#else
static lv_font_fmt_txt_dsc_t font_dsc_fa = {
#endif
    .glyph_bitmap = glyph_bitmap_fa,
    .glyph_dsc = glyph_dsc_fa,
    .cmaps = cmaps_fa,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache_fa
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t fa_icons = {
#else
lv_font_t fa_icons = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 40,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc_fa,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FA_ICONS*/

