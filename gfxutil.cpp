/*
* UAE - The Un*x Amiga Emulator
*
* Common code needed by all the various graphics systems.
*
* (c) 1996 Bernd Schmidt, Ed Hanway, Samuel Devulder
*/

#include "sysconfig.h"
#include "sysdeps.h"
#include "options.h"
#include "custom.h"
#include "rtgmodes.h"
#include "xwin.h"
#include "gfxfilter.h"

#include <math.h>

double getvsyncrate (double hz, int *mult)
{
	if (hz < 0)
		return 0;
	if (hz > 85) {
		*mult = -1;
		return hz / 2;
	}
	if (hz < 35 && hz > 0) {
		*mult = 1;
		return hz * 2;
	}
	*mult = 0;
	return hz;
}

#define RED	0
#define GRN	1
#define BLU	2

unsigned int doMask (int p, int bits, int shift)
{
	/* scale to 0..255, shift to align msb with mask, and apply mask */
	unsigned long val;

	if (flashscreen)
		p ^= 0xff;
	val = p << 24;
	if (!bits)
		return 0;
	val >>= (32 - bits);
	val <<= shift;

	return val;
}

int bits_in_mask (unsigned long mask)
{
	int n = 0;
	while (mask) {
		n += mask & 1;
		mask >>= 1;
	}
	return n;
}

int mask_shift (unsigned long mask)
{
	int n = 0;
	if (!mask)
		return 0;
	while (!(mask & 1)) {
		n++;
		mask >>= 1;
	}
	return n;
}

unsigned int doMask256 (int p, int bits, int shift)
{
	/* p is a value from 0 to 255 (Amiga color value)
	* shift to align msb with mask, and apply mask */

	unsigned long val = p * 0x01010101UL;
	if (bits == 0)
		return 0;
	val >>= (32 - bits);
	val <<= shift;

	return val;
}

static unsigned int doColor (int i, int bits, int shift)
{
	int shift2;

	if (flashscreen)
		i ^= 0xffffffff;
	if(bits >= 8)
		shift2 = 0;
	else
		shift2 = 8 - bits;
	return (i >> shift2) << shift;
}

static unsigned int doAlpha (int alpha, int bits, int shift)
{
	return (alpha & ((1 << bits) - 1)) << shift;
}

static float video_gamma (float value, float gamma, float bri, float con)
{
	double factor;
	float ret;

	value += bri;
	value *= con;

	if (value <= 0.0f)
		return 0.0f;

	factor = pow(255.0f, 1.0f - gamma);
	ret = (float)(factor * pow(value, gamma));

	if (ret < 0.0f)
		ret = 0.0f;

	return ret;
}

static uae_u32 gamma[256 * 3];
static int lf, hf;

static void video_calc_gammatable (void)
{
	int i;
	float bri, con, gam, v;
	uae_u32 vi;

	bri = ((float)(currprefs.gfx_luminance))
		* (128.0f / 1000.0f);
	con = ((float)(currprefs.gfx_contrast + 1000)) / 1000.0f;
	gam = ((float)(1000 - currprefs.gfx_gamma)) / 1000.0f;

	lf = 64 * currprefs.gfx_filter_blur / 1000;
	hf = 256 - lf * 2;

	for (i = 0; i < (256 * 3); i++) {
		v = video_gamma((float)(i - 256), gam, bri, con);

		vi = (uae_u32)v;
		if (vi > 255)
			vi = 255;

		if (currprefs.gfx_luminance == 0 && currprefs.gfx_contrast == 0 && currprefs.gfx_gamma == 0)
			vi = i & 0xff;

		gamma[i] = vi;
	}
}

static uae_u32 limit256 (double v)
{
	v = v * (double)(currprefs.gfx_filter_contrast + 1000) / 1000.0 + currprefs.gfx_filter_luminance / 10.0;
	if (v < 0)
		v = 0;
	if (v > 255)
		v = 255;
	return ((uae_u32)v) & 0xff;
}
static uae_u32 limit256rb (double v)
{
	v *= (double)(currprefs.gfx_filter_saturation + 1000) / 1000.0;
	if (v < -128)
		v = -128;
	if (v > 127)
		v = 127;
	return ((uae_u32)v) & 0xff;
}
static double get_y (int r, int g, int b)
{
	return 0.2989f * r + 0.5866f * g + 0.1145f * b;
}
static uae_u32 get_yh (int r, int g, int b)
{
	return limit256 (get_y (r, g, b) * hf / 256);
}
static uae_u32 get_yl (int r, int g, int b)
{
	return limit256 (get_y (r, g, b) * lf / 256);
}
static uae_u32 get_cb (int r, int g, int b)
{
	return limit256rb (-0.168736f * r - 0.331264f * g + 0.5f * b);
}
static uae_u32 get_cr (int r, int g, int b)
{
	return limit256rb (0.5f * r - 0.418688f * g - 0.081312f * b);
}

extern uae_s32 tyhrgb[65536];
extern uae_s32 tylrgb[65536];
extern uae_s32 tcbrgb[65536];
extern uae_s32 tcrrgb[65536];
extern uae_u32 redc[3 * 256], grec[3 * 256], bluc[3 * 256];

static uae_u32 lowbits (int v, int shift, int lsize)
{
	v >>= shift;
	v &= (1 << lsize) - 1;
	return v;
}

void alloc_colors_picasso (int rw, int gw, int bw, int rs, int gs, int bs, int rgbfmt)
{
	int byte_swap = 0;
	int i;
	int red_bits = 0, green_bits, blue_bits;
	int red_shift, green_shift, blue_shift;
	int bpp = rw + gw + bw;

	switch (rgbfmt)
	{
	case RGBFB_R5G6B5PC:
		red_bits = 5;
		green_bits = 6;
		blue_bits = 5;
		red_shift = 11;
		green_shift = 5;
		blue_shift = 0;
		break;
	case RGBFB_R5G5B5PC:
		red_bits = green_bits = blue_bits = 5;
		red_shift = 10;
		green_shift = 5;
		blue_shift = 0;
		break;
	case RGBFB_R5G6B5:
		red_bits = 5;
		green_bits = 6;
		blue_bits = 5;
		red_shift = 11;
		green_shift = 5;
		blue_shift = 0;
		byte_swap = 1;
		break;
	case RGBFB_R5G5B5:
		red_bits = green_bits = blue_bits = 5;
		red_shift = 10;
		green_shift = 5;
		blue_shift = 0;
		byte_swap = 1;
		break;
	case RGBFB_B5G6R5PC:
		red_bits = 5;
		green_bits = 6;
		blue_bits = 5;
		red_shift = 0;
		green_shift = 5;
		blue_shift = 11;
		break;
	case RGBFB_B5G5R5PC:
		red_bits = green_bits = blue_bits = 5;
		red_shift = 0;
		green_shift = 5;
		blue_shift = 10;
		break;
	default:
		red_bits = rw;
		green_bits = gw;
		blue_bits = bw;
		red_shift = rs;
		green_shift = gs;
		blue_shift = bs;
		break;
	}

	memset (p96_rgbx16, 0, sizeof p96_rgbx16);

	if (red_bits) {
		int lrbits = 8 - red_bits;
		int lgbits = 8 - green_bits;
		int lbbits = 8 - blue_bits;
		int lrmask = (1 << red_bits) - 1;
		int lgmask = (1 << green_bits) - 1;
		int lbmask = (1 << blue_bits) - 1;
		for (i = 65535; i >= 0; i--) {
			uae_u32 r, g, b, c;
			uae_u32 j = byte_swap ? bswap_16 (i) : i;
			r = (((j >>   red_shift) & lrmask) << lrbits) | lowbits (j,   red_shift, lrbits);
			g = (((j >> green_shift) & lgmask) << lgbits) | lowbits (j, green_shift, lgbits);
			b = (((j >>  blue_shift) & lbmask) << lbbits) | lowbits (j,  blue_shift, lbbits);
			c = doMask(r, rw, rs) | doMask(g, gw, gs) | doMask(b, bw, bs);
			if (bpp <= 16)
				c *= 0x00010001;
			p96_rgbx16[i] = c;
		}
	}
}

void alloc_colors_rgb (int rw, int gw, int bw, int rs, int gs, int bs, int aw, int as, int alpha, int byte_swap,
	uae_u32 *rc, uae_u32 *gc, uae_u32 *bc)
{
	int bpp = rw + gw + bw + aw;
	int i;
	for(i = 0; i < 256; i++) {
		int j;

		if (currprefs.gfx_blackerthanblack) {
			j = i * 15 / 16 + 15;
		} else {  
			j = i;
		}
		j += 256;

		rc[i] = doColor (gamma[j], rw, rs) | doAlpha (alpha, aw, as);
		gc[i] = doColor (gamma[j], gw, gs) | doAlpha (alpha, aw, as);
		bc[i] = doColor (gamma[j], bw, bs) | doAlpha (alpha, aw, as);
		if (byte_swap) {
			if (bpp <= 16) {
				rc[i] = bswap_16 (rc[i]);
				gc[i] = bswap_16 (gc[i]);
				bc[i] = bswap_16 (bc[i]);
			} else {
				rc[i] = bswap_32 (rc[i]);
				gc[i] = bswap_32 (gc[i]);
				bc[i] = bswap_32 (bc[i]);
			}
		}
		if (bpp <= 16) {
			/* Fill upper 16 bits of each colour value with
			* a copy of the colour. */
			rc[i] = rc[i] * 0x00010001;
			gc[i] = gc[i] * 0x00010001;
			bc[i] = bc[i] * 0x00010001;
		}
	}
}

void alloc_colors64k (int rw, int gw, int bw, int rs, int gs, int bs, int aw, int as, int alpha, int byte_swap)
{
	int bpp = rw + gw + bw + aw;
	int i, j;

	video_calc_gammatable ();
	j = 256;
	for (i = 0; i < 4096; i++) {
		int r = ((i >> 8) << 4) | (i >> 8);
		int g = (((i >> 4) & 0xf) << 4) | ((i >> 4) & 0x0f);
		int b = ((i & 0xf) << 4) | (i & 0x0f);
		r = gamma[r + j];
		g = gamma[g + j];
		b = gamma[b + j];
		xcolors[i] = doMask(r, rw, rs) | doMask(g, gw, gs) | doMask(b, bw, bs) | doAlpha (alpha, aw, as);
		if (byte_swap) {
			if (bpp <= 16)
				xcolors[i] = bswap_16 (xcolors[i]);
			else
				xcolors[i] = bswap_32 (xcolors[i]);
		}
		if (bpp <= 16) {
			/* Fill upper 16 bits of each colour value
			* with a copy of the colour. */
			xcolors[i] |= xcolors[i] * 0x00010001;
		}
	}
#if defined(AGA) || defined(GFXFILTER)
	alloc_colors_rgb (rw, gw, bw, rs, gs, bs, aw, as, alpha, byte_swap, xredcolors, xgreencolors, xbluecolors);
	/* copy original color table */
	for (i = 0; i < 256; i++) {
		redc[0 * 256 + i] = xredcolors[0];
		grec[0 * 256 + i] = xgreencolors[0];
		bluc[0 * 256 + i] = xbluecolors[0];
		redc[1 * 256 + i] = xredcolors[i];
		grec[1 * 256 + i] = xgreencolors[i];
		bluc[1 * 256 + i] = xbluecolors[i];
		redc[2 * 256 + i] = xredcolors[255];
		grec[2 * 256 + i] = xgreencolors[255];
		bluc[2 * 256 + i] = xbluecolors[255];
	}
	if (usedfilter && usedfilter->yuv) {
		/* create internal 5:6:5 color tables */
		for (i = 0; i < 256; i++) {
			j = i + 256;
			xredcolors[i] = doColor (gamma[j], 5, 11);
			xgreencolors[i] = doColor (gamma[j], 6, 5);
			xbluecolors[i] = doColor (gamma[j], 5, 0);
			if (bpp <= 16) {
				/* Fill upper 16 bits of each colour value with
				* a copy of the colour. */
				xredcolors  [i] = xredcolors  [i] * 0x00010001;
				xgreencolors[i] = xgreencolors[i] * 0x00010001;
				xbluecolors [i] = xbluecolors [i] * 0x00010001;
			}
		}
		for (i = 0; i < 4096; i++) {
			int r = ((i >> 8) << 4) | (i >> 8);
			int g = (((i >> 4) & 0xf) << 4) | ((i >> 4) & 0x0f);
			int b = ((i & 0xf) << 4) | (i & 0x0f);
			r = gamma[r + 256];
			g = gamma[g + 256];
			b = gamma[b + 256];
			xcolors[i] = doMask(r, 5, 11) | doMask(g, 6, 5) | doMask(b, 5, 0);
			if (byte_swap) {
				if (bpp <= 16)
					xcolors[i] = bswap_16 (xcolors[i]);
				else
					xcolors[i] = bswap_32 (xcolors[i]);
			}
			if (bpp <= 16) {
				/* Fill upper 16 bits of each colour value
				* with a copy of the colour. */
				xcolors[i] |= xcolors[i] * 0x00010001;
			}
		}

		/* create RGB 5:6:5 -> YUV tables */
		for (i = 0; i < 65536; i++) {
			uae_u32 r, g, b;
			r = (((i >> 11) & 31) << 3) | lowbits (i, 11, 3);
			r = gamma[r + 256];
			g = (((i >>  5) & 63) << 2) | lowbits (i,  5, 2);
			g = gamma[g + 256];
			b = (((i >>  0) & 31) << 3) | lowbits (i,  0, 3);
			b = gamma[b + 256];
			tyhrgb[i] = get_yh (r, g, b) * 256 * 256;
			tylrgb[i] = get_yl (r, g, b) * 256 * 256;
			tcbrgb[i] = ((uae_s8)get_cb (r, g, b)) * 256;
			tcrrgb[i] = ((uae_s8)get_cr (r, g, b)) * 256;
		}
	}

#endif
	xredcolor_b = rw;
	xgreencolor_b = gw;
	xbluecolor_b = bw;
	xredcolor_s = rs;
	xgreencolor_s = gs;
	xbluecolor_s = bs;
	xredcolor_m = ((1 << rw) - 1) << xredcolor_s;
	xgreencolor_m = ((1 << gw) - 1) << xgreencolor_s;
	xbluecolor_m = ((1 << bw) - 1) << xbluecolor_s;
}
