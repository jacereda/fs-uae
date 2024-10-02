#define FSEMU_INTERNAL
#include "fsemu-font.h"

#include "fsemu-color.h"
#include "fsemu-data.h"
#include "fsemu-image.h"
#include "fsemu-refable.h"
#include "fsemu-util.h"


#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"

int fsemu_font_log_level = FSEMU_LOG_LEVEL_INFO;

#define BMSZ 256

struct fsemu_font {
	FSEMU_REFABLE;
	stbtt_fontinfo font;
	unsigned char bitmap[BMSZ*BMSZ];
	stbtt_bakedchar cdata[96];
	uint baseline;
	uint height;
	float scale;
};

void fsemu_font_ref(fsemu_font_t *font)
{
	fsemu_refable_ref(font);
}

void fsemu_font_unref(fsemu_font_t *font)
{
	fsemu_refable_unref(font);
}

static void fsemu_font_finalize(void *object)
{
	fsemu_font_t *font = (fsemu_font_t *) object;
	fsemu_font_log_debug("Finalizing font %p\n", font);
	free(font);
}

fsemu_font_t *fsemu_font_load(const char *name, int size)
{
	fsemu_font_init();
	fsemu_font_t *font = FSEMU_UTIL_MALLOC0(fsemu_font_t);
	fsemu_refable_init_with_finalizer(font, fsemu_font_finalize);
	void *data;
	int data_size;
	fsemu_data_load(name, &data, &data_size);
	fsemu_font_log_debug("Read %s (%d bytes)\n", name, data_size);
	stbtt_InitFont(&font->font, data, stbtt_GetFontOffsetForIndex(data,0));
	stbtt_BakeFontBitmap(data,0, size, font->bitmap,BMSZ,BMSZ, 32,96, font->cdata); // no guarantee this fits!
	int x0, x1, y0, y1;
	stbtt_GetFontBoundingBox(&font->font, &x0, &y0, &x1, &y1);
	font->scale = stbtt_ScaleForPixelHeight(&font->font, size);
       	font->height = (int)((y1-y0)*font->scale);
	int ascent;
	stbtt_GetFontVMetrics(&font->font, &ascent,0,0);
	font->baseline = (int) (ascent*font->scale);
	free(data);
	fsemu_font_log("Loaded %s (%d)\n", name, size);
	return font;
}

fsemu_image_t *fsemu_font_render_text_to_image(fsemu_font_t *font,
                                               const char *text,
                                               uint32_t color)
{
	if (!*text)  return NULL;
	float x = 0;
	float y = 0;
	stbtt_aligned_quad q;
	for (const char * t = text; *t; t++)
		stbtt_GetBakedQuad(font->cdata, BMSZ,BMSZ, *t-32, &x,&y,&q,1);
	uint w = q.x1 + 1;
	uint h = font->height;
	uint32_t * data = calloc(w*h*sizeof(*data), 1);
	x=0;
	y=0;
	uint baseline = font->baseline;
	for (const char * t = text; *t; t++) {
		fsemu_assert(*t >= 32 && *t < 128);
		stbtt_GetBakedQuad(font->cdata, BMSZ, BMSZ, *t-32, &x, &y, &q, 1);
		fsemu_assert(q.y1-q.y0 <= h);
		for (uint y=q.y0+baseline, t = q.t0*BMSZ; y < q.y1+baseline; y++, t++) {
			uint sz = (q.s1-q.s0)*BMSZ;
			const uint8_t * src = font->bitmap + t * BMSZ + (int)(q.s0*BMSZ);
			uint32_t * dst = data + y*w + (int)q.x0;
			fsemu_assert(dst+sz <= data+w*h);
			for (uint i = 0; i < sz; i++)
				dst[i] = (src[i]<<24) | (color & 0xffffff);
		}
	}
	fsemu_image_t im = {
		.bpp = 4,
		.depth = 32,
		.height = h,
		.stride = w * sizeof(*data),
		.width = w,
		.data = data,
		.free_function = free,
		.free_param = data,
	};
	fsemu_image_t * r = malloc(sizeof(*r));
	*r = im;
	return r;
}

void fsemu_font_init(void)
{
	fsemu_return_if_already_initialized();
	fsemu_data_init();
	fsemu_font_log("Initializing font module\n");
}
