/*******************************************************************************
 * Size: 24 px
 * Bpp: 1
 * Opts: --bpp 1 --size 24 --no-compress --font UbuntuCondensed-Regular.ttf --symbols 0123456789- %°Cm.psiVhk --format lvgl -o ubuntu_24.c
 ******************************************************************************/
#ifndef UBUNTU_24
#define UBUNTU_24 1
#endif

#if UBUNTU_24

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap_u24[] = {
    /* U+0020 " " */
    0x0,

    /* U+0025 "%" */
    0x78, 0xc3, 0xc6, 0x33, 0x31, 0x9b, 0xc, 0xd8,
    0x66, 0x83, 0x3c, 0xf, 0x60, 0x7a, 0xf0, 0x37,
    0x81, 0xe6, 0x1b, 0x30, 0xd9, 0x86, 0xcc, 0x66,
    0x63, 0x1e, 0x10, 0xf0,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xff, 0x80,

    /* U+0030 "0" */
    0x3c, 0x7e, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x7e,
    0x3c,

    /* U+0031 "1" */
    0x19, 0xdf, 0xf5, 0x8c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x63, 0x18,

    /* U+0032 "2" */
    0x79, 0xfa, 0x38, 0x30, 0x60, 0xc3, 0x6, 0x18,
    0x30, 0xc3, 0x6, 0x1c, 0x30, 0x7f, 0xfe,

    /* U+0033 "3" */
    0x79, 0xf8, 0x38, 0x30, 0x60, 0xc3, 0x3e, 0x7c,
    0x1c, 0x18, 0x30, 0x60, 0xe3, 0xfe, 0x78,

    /* U+0034 "4" */
    0x6, 0x7, 0x7, 0x83, 0xc1, 0x61, 0xb0, 0x98,
    0xcc, 0x66, 0x23, 0x31, 0x9f, 0xff, 0xf8, 0x30,
    0x18, 0xc, 0x6, 0x0,

    /* U+0035 "5" */
    0x7e, 0xfd, 0x83, 0x6, 0xc, 0x18, 0x3c, 0x1c,
    0x1c, 0x18, 0x30, 0x60, 0xc3, 0x7e, 0xf8,

    /* U+0036 "6" */
    0xe, 0x1e, 0x30, 0x60, 0x60, 0xc0, 0xfc, 0xfe,
    0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67, 0x7e,
    0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0x7, 0x6, 0x6, 0xc, 0xc, 0xc,
    0x18, 0x18, 0x18, 0x18, 0x10, 0x30, 0x30, 0x30,
    0x30,

    /* U+0038 "8" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0x66, 0x7e,
    0x3c, 0x6e, 0xc7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0039 "9" */
    0x3c, 0x7e, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xe3, 0x7f, 0x3f, 0x3, 0x6, 0x6, 0xc, 0x78,
    0x70,

    /* U+0043 "C" */
    0x1f, 0x1f, 0xdc, 0x2c, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xe, 0x3, 0x1,
    0xc2, 0x7f, 0x1f, 0x0,

    /* U+0056 "V" */
    0x60, 0x6c, 0xd, 0x81, 0xb0, 0x37, 0xe, 0x61,
    0x8c, 0x31, 0x86, 0x30, 0xc3, 0x30, 0x66, 0xc,
    0xc1, 0x90, 0x1e, 0x3, 0xc0, 0x78, 0x6, 0x0,

    /* U+0068 "h" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xfe,
    0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0xfc, 0x3f, 0xff, 0xff, 0xf0,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc6, 0xc6,
    0xcc, 0xdc, 0xd8, 0xf0, 0xf0, 0xd8, 0xdc, 0xcc,
    0xc6, 0xc6, 0xc3,

    /* U+006D "m" */
    0x7c, 0xf3, 0xff, 0xec, 0x71, 0xf0, 0xc3, 0xc3,
    0xf, 0xc, 0x3c, 0x30, 0xf0, 0xc3, 0xc3, 0xf,
    0xc, 0x3c, 0x30, 0xf0, 0xc3, 0xc3, 0xc,

    /* U+0070 "p" */
    0xf8, 0xfe, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc6, 0xfe, 0xfc, 0xc0, 0xc0, 0xc0,
    0xc0,

    /* U+0073 "s" */
    0x7b, 0xec, 0x30, 0xc1, 0x83, 0x86, 0xc, 0x30,
    0xfe, 0xf0,

    /* U+00B0 "°" */
    0x7b, 0xfc, 0xf3, 0xfd, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc_u24[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 75, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 248, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 89, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 30, .adv_w = 89, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 165, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 165, .box_w = 5, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 165, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 165, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 165, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 165, .box_w = 7, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 165, .box_w = 8, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 165, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 165, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 165, .box_w = 8, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 180, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 191, .box_w = 11, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 185, .box_w = 8, .box_h = 19, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 93, .box_w = 2, .box_h = 18, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 164, .box_w = 8, .box_h = 19, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 268, .box_w = 14, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 179, .box_w = 8, .box_h = 17, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 320, .adv_w = 131, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 111, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 13}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0_u24[] = {
    0x0, 0x5, 0xd, 0xe, 0x10, 0x11, 0x12, 0x13,
    0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x23, 0x36,
    0x48, 0x49, 0x4b, 0x4d, 0x50, 0x53, 0x90
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps_u24[] =
{
    {
        .range_start = 32, .range_length = 145, .glyph_id_start = 1,
        .unicode_list = unicode_list_0_u24, .glyph_id_ofs_list = NULL, .list_length = 23, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    3, 15,
    3, 16,
    4, 15,
    15, 3,
    15, 4,
    15, 15,
    15, 16,
    16, 3,
    16, 4,
    16, 15,
    16, 16,
    16, 20,
    16, 21,
    16, 22,
    19, 3,
    21, 3
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    8, -4, -13, -11, 12, -4, 12, -4,
    -19, -4, 12, -6, -6, -8, -8, 6
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 16,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc_u24 = {
#else
static lv_font_fmt_txt_dsc_t font_dsc_u24 = {
#endif
    .glyph_bitmap = glyph_bitmap_u24,
    .glyph_dsc = glyph_dsc_u24,
    .cmaps = cmaps_u24,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
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
const lv_font_t ubuntu_24 = {
#else
lv_font_t ubuntu_24 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 23,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -3,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc_u24,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UBUNTU_24*/

