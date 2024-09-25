#ifndef UAE_PICASSO96_H
#define UAE_PICASSO96_H

#include "uae/types.h"
#include "traps.h"

void picasso96_alloc (TrapContext* ctx);
uae_u32 picasso_demux (uae_u32 arg, TrapContext *ctx);

#if defined WIN32 || defined FSUAE

#include "picasso96_win.h"

#else
/*
 * UAE - The U*nix Amiga Emulator
 *
 * Picasso96 Support Module Header
 *
 * Copyright 1997 Brian King <Brian_King@Mitel.com, Brian_King@Cloanto.com>
 */

#if defined PICASSO96_SUPPORTED

#define PICASSO96


/* Seems the same routines copy back and forth ;-) */
#define PIC_READ (S_READ|S_WRITE)
#define PIC_WRITE (S_READ|S_WRITE)

#define JAM1 0
#define JAM2 1
#define COMP 2
#define INVERS 4

typedef enum {
    BLIT_FALSE,
    BLIT_NOR,
    BLIT_ONLYDST,
    BLIT_NOTSRC,
    BLIT_ONLYSRC,
    BLIT_NOTDST,
    BLIT_EOR,
    BLIT_NAND,
    BLIT_AND,
    BLIT_NEOR,
    BLIT_DST,
    BLIT_NOTONLYSRC,
    BLIT_SRC,
    BLIT_NOTONLYDST,
    BLIT_OR,
    BLIT_TRUE,
    BLIT_LAST
} BLIT_OPCODE;

/************************************************************************/
/* Types for BoardType Identification
 */
typedef enum {
	BT_NoBoard,
	BT_oMniBus,
	BT_Graffity,
	BT_CyberVision,
	BT_Domino,
	BT_Merlin,
	BT_PicassoII,
	BT_Piccolo,
	BT_RetinaBLT,
	BT_Spectrum,
	BT_PicassoIV,
	BT_PiccoloSD64,
	BT_A2410,
	BT_Pixel64,
	BT_uaegfx,
	BT_CVision3D,
	BT_Altais,
	BT_Prototype1,
	BT_Prototype2,
	BT_Prototype3,
	BT_Prototype4,
	BT_Prototype5,
	BT_MaxBoardTypes
} BTYPE;

struct ScreenResolution
{
    uae_u32 width;  /* in pixels */
    uae_u32 height; /* in pixels */
};

#define MAX_PICASSO_MODES 64

struct PicassoResolution
{
    struct Resolutions *next;
    struct ScreenResolution res;
    int depth;
    int refresh;
    char name[25];
};
extern struct PicassoResolution DisplayModes[MAX_PICASSO_MODES];


/* Types for RGBFormat used */
typedef enum {
    RGBFB_NONE,		/* no valid RGB format (should not happen) */
    RGBFB_CLUT,		/* palette mode, set colors when opening screen using
			   tags or use SetRGB32/LoadRGB32(...) */
    RGBFB_R8G8B8,	/* TrueColor RGB (8 bit each) */
    RGBFB_B8G8R8,	/* TrueColor BGR (8 bit each) */
    RGBFB_R5G6B5PC,	/* HiColor16 (5 bit R, 6 bit G, 5 bit B),
			   format: gggbbbbbrrrrrggg */
    RGBFB_R5G5B5PC,	/* HiColor15 (5 bit each), format: gggbbbbb0rrrrrgg */
    RGBFB_A8R8G8B8,	/* 4 Byte TrueColor ARGB (A unused alpha channel) */
    RGBFB_A8B8G8R8,	/* 4 Byte TrueColor ABGR (A unused alpha channel) */
    RGBFB_R8G8B8A8,	/* 4 Byte TrueColor RGBA (A unused alpha channel) */
    RGBFB_B8G8R8A8,	/* 4 Byte TrueColor BGRA (A unused alpha channel) */
    RGBFB_R5G6B5,	/* HiColor16 (5 bit R, 6 bit G, 5 bit B),
			   format: rrrrrggggggbbbbb */
    RGBFB_R5G5B5,	/* HiColor15 (5 bit each), format: 0rrrrrgggggbbbbb */
    RGBFB_B5G6R5PC,	/* HiColor16 (5 bit R, 6 bit G, 5 bit B),
			   format: gggrrrrrbbbbbggg */
    RGBFB_B5G5R5PC,	/* HiColor15 (5 bit each), format: gggrrrrr0bbbbbbgg */

    /* By now, the following formats are for use with a hardware window only
       (bitmap operations may be implemented incompletely) */

    RGBFB_Y4U2V2,	/* 2 Byte TrueColor YUV (CCIR recommendation CCIR601).
			   Each two-pixel unit is stored as one longword
			   containing luminance (Y) for each of the two pixels,
			   and chrominance (U,V) for alternate pixels.
			   The missing chrominance values are generated by
			   interpolation. (Y1-U0-Y0-V0) */
    RGBFB_Y4U1V1,	/* 1 Byte TrueColor ACCUPAK. Four adjacent pixels form
			   a packet of 5 bits Y (luminance) each pixel and 6 bits
			   U and V (chrominance) shared by the four pixels */

    RGBFB_MaxFormats
} RGBFTYPE;

#define RGBFF_NONE	(1<<RGBFB_NONE)
#define RGBFF_CLUT	(1<<RGBFB_CLUT)
#define RGBFF_R8G8B8	(1<<RGBFB_R8G8B8)
#define RGBFF_B8G8R8	(1<<RGBFB_B8G8R8)
#define RGBFF_R5G6B5PC	(1<<RGBFB_R5G6B5PC)
#define RGBFF_R5G5B5PC	(1<<RGBFB_R5G5B5PC)
#define RGBFF_A8R8G8B8	(1<<RGBFB_A8R8G8B8)
#define RGBFF_A8B8G8R8	(1<<RGBFB_A8B8G8R8)
#define RGBFF_R8G8B8A8	(1<<RGBFB_R8G8B8A8)
#define RGBFF_B8G8R8A8	(1<<RGBFB_B8G8R8A8)
#define RGBFF_R5G6B5	(1<<RGBFB_R5G6B5)
#define RGBFF_R5G5B5	(1<<RGBFB_R5G5B5)
#define RGBFF_B5G6R5PC	(1<<RGBFB_B5G6R5PC)
#define RGBFF_B5G5R5PC	(1<<RGBFB_B5G5R5PC)
#define RGBFF_Y4U2V2	(1<<RGBFB_Y4U2V2)
#define RGBFF_Y4U1V1	(1<<RGBFB_Y4U1V1)

#define RGBMASK_8BIT RGBFF_CLUT
#define RGBMASK_16BIT (RGBFF_R5G6B5PC | RGBFF_B5G6R5PC | RGBFF_R5G6B5)
#define RGBMASK_15BIT (RGBFF_R5G5B5PC | RGBFF_B5G5R5PC | RGBFF_R5G5B5)
#define RGBMASK_24BIT (RGBFF_R8G8B8 | RGBFF_B8G8R8)
#define RGBMASK_32BIT (RGBFF_A8R8G8B8 | RGBFF_A8B8G8R8 | RGBFF_R8G8B8A8 | RGBFF_B8G8R8A8)

/************************************************************************/

#define RGBFF_PLANAR	RGBFF_NONE
#define RGBFF_CHUNKY	RGBFF_CLUT

#define RGBFB_PLANAR	RGBFB_NONE
#define RGBFB_CHUNKY	RGBFB_CLUT

/************************************************************************/

enum {
    PLANAR,
    CHUNKY,
    HICOLOR,
    TRUECOLOR,
    TRUEALPHA,
    MAXMODES
};

/************************************************************************/
struct MyCLUTEntry {
    uae_u8 Red;
    uae_u8 Green;
    uae_u8 Blue;
    uae_u8 Pad;
};

struct ColorIndexMapping {
    uae_u32 ColorMask;
    uae_u32 Colors[256];
};

struct CLUTEntry {
    uae_u8 Red;
    uae_u8 Green;
    uae_u8 Blue;
};

#define PSSO_BitMap_BytesPerRow 0
#define PSSO_BitMap_Rows 2
#define PSSO_BitMap_Flags 4
#define PSSO_BitMap_Depth 5
#define PSSO_BitMap_pad 6
#define PSSO_BitMap_Planes 8
#define PSSO_BitMap_sizeof 40

struct BitMap
{
    uae_u16 BytesPerRow;
    uae_u16 Rows;
    uae_u8 Flags;
    uae_u8 Depth;
    uae_u16 pad;
    uae_u8 *Planes[8];
};

/************************************************************************/

#define SETTINGSNAMEMAXCHARS		30
#define BOARDNAMEMAXCHARS		30

struct Settings {
    uae_u32					BoardType;
    /* a value describing assignment to nth board local to boardtype
     * to be used for reassignment when boards are added or removed.  */
    uae_u16					LocalOrdering;
    uae_s16					LastSelected;
    char					NameField[SETTINGSNAMEMAXCHARS];
    /* neu! */
    char					*BoardName;
};

#define MAXRESOLUTIONNAMELENGTH 22

/********************************
 * only used within rtg.library *
 ********************************/

#define PSSO_LibResolution_P96ID 14
#define PSSO_LibResolution_Name 20
#define PSSO_LibResolution_DisplayID 42 /* Name + MAXRESOLUTIONNAMELENGTH */
#define PSSO_LibResolution_Width 46
#define PSSO_LibResolution_Height 48
#define PSSO_LibResolution_Flags 50
#define PSSO_LibResolution_Modes 52
#define PSSO_LibResolution_BoardInfo (52 + MAXMODES*4)
#define PSSO_LibResolution_sizeof (60 + MAXMODES*4)

struct LibResolution {
    char P96ID[6];
    char Name[MAXRESOLUTIONNAMELENGTH];
    uae_u32 DisplayID;
    uae_u16 Width;
    uae_u16 Height;
    uae_u16 Flags;
    uaecptr Modes[MAXMODES];
    uaecptr BoardInfo;
};

#define P96B_FAMILY	0			/* obsolete (Resolution is an entire family) */
#define P96B_PUBLIC	1			/* Resolution should be added to the public */
#define P96B_MONITOOL	2

#define P96F_FAMILY	(1<<P96B_FAMILY)	/* obsolete */
#define P96F_PUBLIC	(1<<P96B_PUBLIC)
#define P96F_MONITOOL	(1<<P96B_MONITOOL)

#define PSSO_ModeInfo_OpenCount 14
#define PSSO_ModeInfo_Active 16
#define PSSO_ModeInfo_Width 18
#define PSSO_ModeInfo_Height 20
#define PSSO_ModeInfo_Depth 22
#define PSSO_ModeInfo_Flags 23
#define PSSO_ModeInfo_HorTotal 24
#define PSSO_ModeInfo_HorBlankSize 26
#define PSSO_ModeInfo_HorSyncStart 28
#define PSSO_ModeInfo_HorSyncSize 30
#define PSSO_ModeInfo_HorSyncSkew 32
#define PSSO_ModeInfo_HorEnableSkew 33
#define PSSO_ModeInfo_VerTotal 34
#define PSSO_ModeInfo_VerBlankSize 36
#define PSSO_ModeInfo_VerSyncStart 38
#define PSSO_ModeInfo_VerSyncSize 40
#define PSSO_ModeInfo_first_union 42
#define PSSO_ModeInfo_second_union 43
#define PSSO_ModeInfo_PixelClock 44
#define PSSO_ModeInfo_sizeof 48

#define PSSO_RenderInfo_Memory 0
#define PSSO_RenderInfo_BytesPerRow 4
#define PSSO_RenderInfo_pad 6
#define PSSO_RenderInfo_RGBFormat 8
#define PSSO_RenderInfo_sizeof 12

struct RenderInfo {
    uae_u8 *Memory;
    uae_s16 BytesPerRow;
    uae_s16 pad;
    RGBFTYPE RGBFormat;
    uaecptr AMemory;
};

#define PSSO_Pattern_Memory 0
#define PSSO_Pattern_XOffset 4
#define PSSO_Pattern_YOffset 6
#define PSSO_Pattern_FgPen 8
#define PSSO_Pattern_BgPen 12
#define PSSO_Pattern_Size 16
#define PSSO_Pattern_DrawMode 17
#define PSSO_Pattern_sizeof 18
struct Pattern {
    char *Memory;
    uae_u16 XOffset, YOffset;
    uae_u32 FgPen, BgPen;
    uae_u8 Size;					/* Width: 16, Height: (1<<pat_Size) */
    uae_u8 DrawMode;
};

#define PSSO_Template_Memory 0
#define PSSO_Template_BytesPerRow 4
#define PSSO_Template_XOffset 6
#define PSSO_Template_DrawMode 7
#define PSSO_Template_FgPen 8
#define PSSO_Template_BgPen 12
#define PSSO_Template_sizeof 16

struct Template {
    char *Memory;
    uae_s16 BytesPerRow;
    uae_u8 XOffset;
    uae_u8 DrawMode;
    uae_u32 FgPen;
    uae_u32 BgPen;
};

#define PSSO_BitMapExtra_BoardNode	  0
#define PSSO_BitMapExtra_HashChain	  8 /* BoardNode is 8-bytes */
#define PSSO_BitMapExtra_Match		 12
#define PSSO_BitMapExtra_BitMap		 16
#define PSSO_BitMapExtra_BoardInfo	 20
#define PSSO_BitMapExtra_MemChunk	 24
#define PSSO_BitMapExtra_RenderInfo	 28
#define PSSO_BitMapExtra_Width		 40 /* RenderInfo is 12-bytes */
#define PSSO_BitMapExtra_Height		 42
#define PSSO_BitMapExtra_Flags		 44
#define PSSO_BitMapExtra_BaseLevel	 46
#define PSSO_BitMapExtra_CurrentLevel	 48
#define PSSO_BitMapExtra_CompanionMaster 50
#define PSSO_BitMapExtra_Last		 54

#define PSSO_BoardInfo_RegisterBase		   0
#define PSSO_BoardInfo_MemoryBase		   PSSO_BoardInfo_RegisterBase + 4
#define PSSO_BoardInfo_MemoryIOBase		   PSSO_BoardInfo_MemoryBase + 4
#define PSSO_BoardInfo_MemorySize		   PSSO_BoardInfo_MemoryIOBase + 4
#define PSSO_BoardInfo_BoardName		   PSSO_BoardInfo_MemorySize + 4
#define PSSO_BoardInfo_VBIName			   PSSO_BoardInfo_BoardName + 4
#define PSSO_BoardInfo_CardBase			   PSSO_BoardInfo_VBIName + 32
#define PSSO_BoardInfo_ChipBase			   PSSO_BoardInfo_CardBase + 4
#define PSSO_BoardInfo_ExecBase			   PSSO_BoardInfo_ChipBase + 4
#define PSSO_BoardInfo_UtilBase			   PSSO_BoardInfo_ExecBase + 4
#define PSSO_BoardInfo_HardInterrupt		   PSSO_BoardInfo_UtilBase + 4
#define PSSO_BoardInfo_SoftInterrupt		   PSSO_BoardInfo_HardInterrupt + 22 /* The HardInterrupt is 22-bytes */
#define PSSO_BoardInfo_BoardLock		   PSSO_BoardInfo_SoftInterrupt + 22 /* The SoftInterrupt is 22-bytes */
#define PSSO_BoardInfo_ResolutionsList		   PSSO_BoardInfo_BoardLock + 46 /* On the BoardLock, we were having some fun... */
#define PSSO_BoardInfo_BoardType		   PSSO_BoardInfo_ResolutionsList + 12 /* The ResolutionsList is 12-bytes */
#define PSSO_BoardInfo_PaletteChipType		   PSSO_BoardInfo_BoardType + 4
#define PSSO_BoardInfo_GraphicsControllerType	   PSSO_BoardInfo_PaletteChipType + 4
#define PSSO_BoardInfo_MoniSwitch		   PSSO_BoardInfo_GraphicsControllerType + 4
#define PSSO_BoardInfo_BitsPerCannon		   PSSO_BoardInfo_MoniSwitch + 2
#define PSSO_BoardInfo_Flags			   PSSO_BoardInfo_BitsPerCannon + 2
#define PSSO_BoardInfo_SoftSpriteFlags		   PSSO_BoardInfo_Flags + 4
#define PSSO_BoardInfo_ChipFlags		   PSSO_BoardInfo_SoftSpriteFlags + 2
#define PSSO_BoardInfo_CardFlags		   PSSO_BoardInfo_ChipFlags + 2
#define PSSO_BoardInfo_BoardNum			   PSSO_BoardInfo_CardFlags + 4
#define PSSO_BoardInfo_RGBFormats		   PSSO_BoardInfo_BoardNum + 2
#define PSSO_BoardInfo_MaxHorValue		   PSSO_BoardInfo_RGBFormats + 2
#define PSSO_BoardInfo_MaxVerValue		   PSSO_BoardInfo_MaxHorValue + MAXMODES*2
#define PSSO_BoardInfo_MaxHorResolution		   PSSO_BoardInfo_MaxVerValue + MAXMODES*2
#define PSSO_BoardInfo_MaxVerResolution		   PSSO_BoardInfo_MaxHorResolution + MAXMODES*2
#define PSSO_BoardInfo_MaxMemorySize		   PSSO_BoardInfo_MaxVerResolution + MAXMODES*2
#define PSSO_BoardInfo_MaxChunkSize		   PSSO_BoardInfo_MaxMemorySize + 4
#define PSSO_BoardInfo_MemoryClock		   PSSO_BoardInfo_MaxChunkSize + 4
#define PSSO_BoardInfo_PixelClockCount		   PSSO_BoardInfo_MemoryClock + 4
#define PSSO_BoardInfo_AllocCardMem		   PSSO_BoardInfo_PixelClockCount + MAXMODES*4
#define PSSO_BoardInfo_SpecialFeatures		   PSSO_BoardInfo_AllocCardMem + 68*4 /* 68 function pointers */
#define PSSO_BoardInfo_ModeInfo			   PSSO_BoardInfo_SpecialFeatures + 12 /* SpecialFeatures is 12-bytes */
#define PSSO_BoardInfo_RGBFormat		   PSSO_BoardInfo_ModeInfo + 4
#define PSSO_BoardInfo_XOffset			   PSSO_BoardInfo_RGBFormat + 4
#define PSSO_BoardInfo_YOffset			   PSSO_BoardInfo_XOffset + 2
#define PSSO_BoardInfo_Depth			   PSSO_BoardInfo_YOffset + 2
#define PSSO_BoardInfo_ClearMask		   PSSO_BoardInfo_Depth + 1
#define PSSO_BoardInfo_Border			   PSSO_BoardInfo_ClearMask + 1
#define PSSO_BoardInfo_Mask			   PSSO_BoardInfo_Border + 2 /* BOOL type is only 2-bytes! */
#define PSSO_BoardInfo_CLUT			   PSSO_BoardInfo_Mask + 4
#define PSSO_BoardInfo_ViewPort			   PSSO_BoardInfo_CLUT + 3*256
#define PSSO_BoardInfo_VisibleBitMap		   PSSO_BoardInfo_ViewPort + 4
#define PSSO_BoardInfo_BitMapExtra		   PSSO_BoardInfo_VisibleBitMap + 4
#define PSSO_BoardInfo_BitMapList		   PSSO_BoardInfo_BitMapExtra + 4
#define PSSO_BoardInfo_MemList			   PSSO_BoardInfo_BitMapList + 12 /* BitMapList is 12-bytes */
#define PSSO_BoardInfo_MouseX			   PSSO_BoardInfo_MemList + 12 /* MemList is 12-bytes */
#define PSSO_BoardInfo_MouseY			   PSSO_BoardInfo_MouseX + 2
#define PSSO_BoardInfo_MouseWidth		   PSSO_BoardInfo_MouseY + 2
#define PSSO_BoardInfo_MouseHeight		   PSSO_BoardInfo_MouseWidth + 1
#define PSSO_BoardInfo_MouseXOffset		   PSSO_BoardInfo_MouseHeight + 1
#define PSSO_BoardInfo_MouseYOffset		   PSSO_BoardInfo_MouseXOffset + 1
#define PSSO_BoardInfo_MouseImage		   PSSO_BoardInfo_MouseYOffset + 1
#define PSSO_BoardInfo_MousePens		   PSSO_BoardInfo_MouseImage + 4
#define PSSO_BoardInfo_MouseRect		   PSSO_BoardInfo_MousePens + 4
#define PSSO_BoardInfo_MouseChunky		   PSSO_BoardInfo_MouseRect + 8 /* MouseRect is 8-bytes */
#define PSSO_BoardInfo_MouseRendered		   PSSO_BoardInfo_MouseChunky + 4
#define PSSO_BoardInfo_MouseSaveBuffer		   PSSO_BoardInfo_MouseRendered + 4

struct BoardInfo {
    uae_u8 *RegisterBase, *MemoryBase, *MemoryIOBase;
    uae_u32 MemorySize;
    char *BoardName, VBIName[32];

    uae_u16 MoniSwitch;
    uae_u16 BitsPerCannon;
    uae_u32 Flags;
    uae_u16 SoftSpriteFlags;
    uae_u16 ChipFlags;	/* private, chip specific, not touched by RTG */
    uae_u32 CardFlags;	/* private, card specific, not touched by RTG */

    uae_u16 BoardNum;
    uae_s16 RGBFormats;

    uae_u16 MaxHorValue[MAXMODES];
    uae_u16 MaxVerValue[MAXMODES];
    uae_u16 MaxHorResolution[MAXMODES];
    uae_u16 MaxVerResolution[MAXMODES];
    uae_u32 MaxMemorySize, MaxChunkSize;
};

/* BoardInfo flags */
/*  0-15: hardware flags */
/* 16-31: user flags */
#define BIB_HARDWARESPRITE	0	/* board has hardware sprite */
#define BIB_NOMEMORYMODEMIX	1	/* board does not support modifying planar bitmaps while displaying chunky and vice versa */
#define BIB_NEEDSALIGNMENT	2	/* bitmaps have to be aligned (not yet supported!) */
#define BIB_DBLSCANDBLSPRITEY	8	/* hardware sprite y position is doubled on doublescan display modes */
#define BIB_ILACEHALFSPRITEY	9	/* hardware sprite y position is halved on interlace display modes */
#define BIB_ILACEDBLROWOFFSET	10	/* doubled row offset in interlaced display modes needs additional horizontal bit */

#define BIB_FLICKERFIXER	12	/* board can flicker fix Amiga RGB signal */
#define BIB_VIDEOCAPTURE	13	/* board can capture video data to a memory area */
#define BIB_VIDEOWINDOW		14	/* board can display a second mem area as a pip */
#define BIB_BLITTER		15	/* board has blitter */

#define BIB_HIRESSPRITE		16	/* mouse sprite has double resolution */
#define BIB_BIGSPRITE		17	/* user wants big mouse sprite */
#define BIB_BORDEROVERRIDE	18	/* user wants to override system overscan border prefs */
#define BIB_BORDERBLANK		19	/* user wants border blanking */
#define BIB_INDISPLAYCHAIN	20	/* board switches Amiga signal */
#define BIB_QUIET		21	/* not yet implemented */
#define BIB_NOMASKBLITS		22	/* perform blits without taking care of mask */
#define BIB_NOC2PBLITS		23	/* use CPU for planar to chunky conversions */
#define BIB_NOBLITTER		24	/* disable all blitter functions */

#define BIB_IGNOREMASK	BIB_NOMASKBLITS

#define BIF_HARDWARESPRITE	(1<<BIB_HARDWARESPRITE)
#define BIF_NOMEMORYMODEMIX	(1<<BIB_NOMEMORYMODEMIX)
#define BIF_NEEDSALIGNMENT	(1<<BIB_NEEDSALIGNMENT)
#define BIF_DBLSCANDBLSPRITEY	(1<<BIB_DBLSCANDBLSPRITEY)
#define BIF_ILACEHALFSPRITEY	(1<<BIB_ILACEHALFSPRITEY)
#define BIF_ILACEDBLROWOFFSET	(1<<BIB_ILACEDBLROWOFFSET)
#define BIF_FLICKERFIXER	(1<<BIB_FLICKERFIXER)
#define BIF_VIDEOCAPTURE	(1<<BIB_VIDEOCAPTURE)
#define BIF_VIDEOWINDOW		(1<<BIB_VIDEOWINDOW)
#define BIF_BLITTER		(1<<BIB_BLITTER)
#define BIF_HIRESSPRITE		(1<<BIB_HIRESSPRITE)
#define BIF_BIGSPRITE		(1<<BIB_BIGSPRITE)
#define BIF_BORDEROVERRIDE	(1<<BIB_BORDEROVERRIDE)
#define BIF_BORDERBLANK		(1<<BIB_BORDERBLANK)
#define BIF_INDISPLAYCHAIN	(1<<BIB_INDISPLAYCHAIN)
#define BIF_QUIET		(1<<BIB_QUIET)
#define BIF_NOMASKBLITS		(1<<BIB_NOMASKBLITS)
#define BIF_NOC2PBLITS		(1<<BIB_NOC2PBLITS)
#define BIF_NOBLITTER		(1<<BIB_NOBLITTER)

#define BIF_IGNOREMASK	BIF_NOMASKBLITS

/************************************************************************/
struct picasso96_state_struct
{
    uae_u32		RGBFormat;   /* true-colour, CLUT, hi-colour, etc. */
    struct MyCLUTEntry	CLUT[256];   /* Duh! */
    uaecptr		Address;     /* Active screen address (Amiga-side) */
    uaecptr		Extent;	     /* End address of screen (Amiga-side) */
    uae_u16		Width;	     /* Active display width  (From SetGC) */
    uae_u16		VirtualWidth;/* Total screen width (From SetPanning) */
    uae_u16		BytesPerRow; /* Total screen width in bytes (From SetGC) */
    uae_u16		Height;	     /* Active display height (From SetGC) */
    uae_u16		VirtualHeight; /* Total screen height */
    uae_u8		GC_Depth;    /* From SetGC() */
    uae_u8		GC_Flags;    /* From SetGC() */
    long		XOffset;     /* From SetPanning() */
    long		YOffset;     /* From SetPanning() */
    uae_u8		SwitchState; /* From SetSwitch() - 0 is Amiga, 1 is Picasso */
    uae_u8		BytesPerPixel;
    uae_u8		CardFound;
};

extern void InitPicasso96 (void);

extern uae_u32 picasso_SetDisplay (void);
extern uae_u32 picasso_WaitVerticalSync (void);
extern uae_u32 picasso_CalculateBytesPerRow (void);
extern uae_u32 picasso_FillRect (void);
extern uae_u32 picasso_BlitRect (void);
extern uae_u32 picasso_InvertRect (void);
extern uae_u32 picasso_SetPanning (void);
extern uae_u32 picasso_SetGC (void);
extern uae_u32 picasso_SetDAC (void);
extern uae_u32 picasso_SetColorArray (void);
extern uae_u32 picasso_SetSwitch (void);
extern uae_u32 picasso_SetSwitch (void);
extern uae_u32 picasso_FindCard (void);
extern uae_u32 picasso_InitCard (void);
extern uae_u32 picasso_BlitPlanar2Chunky (void);
extern uae_u32 picasso_BlitPlanar2Direct (void);
extern uae_u32 picasso_BlitTemplate (void);
extern uae_u32 picasso_BlitPattern (void);
extern uae_u32 picasso_BlitRectNoMaskComplete (void);

extern uae_u32 gfxmem_mask;
extern uae_u8 *gfxmemory;

extern int uaegfx_card_found;

extern struct picasso96_state_struct picasso96_state;

#ifdef _WIN32
extern unsigned int timer_id;
#endif

extern int DX_Fill (int dstx, int dsty, int width, int height, uae_u32 color, RGBFTYPE rgbtype);
extern int DX_Blit (int srcx, int srcy, int dstx, int dsty, int width, int height, BLIT_OPCODE opcode);
extern void DX_BlitRectFromBuffer (struct RenderInfo *ri, uae_u8* buffer, uae_u16 dstx, uae_u16 dsty, uae_u16 w, uae_u16 h);
extern void DX_InvertRect (struct RenderInfo *ri, uae_u16 X, uae_u16 Y, uae_u16 Width, uae_u16 Height);
extern void DX_SetPalette (int start, int count);
extern void DX_SetPalette_vsync (void);
extern int DX_FillResolutions (uae_u16 *);
extern int DX_BitsPerCannon (void);
extern void DX_Invalidate (int first, int last);
extern void picasso_enablescreen (int on);
extern void picasso_refresh (int call_setpalette);
extern void picasso_handle_vsync (void);

extern uae_u8 *gfxmemory;

/* This structure describes the UAE-side framebuffer for the Picasso
 * screen.  */
struct picasso_vidbuf_description {
    int width, height, depth;
    int rowbytes, pixbytes;
    int extra_mem; /* nonzero if there's a second buffer that must be updated */
    uae_u32 rgbformat;
    uae_u32 selected_rgbformat;
    uae_u32 clut[256];
};

extern struct picasso_vidbuf_description picasso_vidinfo;

extern void gfx_set_picasso_modeinfo (int w, int h, int d, int rgbfmt);
extern void gfx_set_picasso_baseaddr (uaecptr);
extern void gfx_set_picasso_state (int on);
extern uae_u8 *gfx_lock_picasso (void);
extern void gfx_unlock_picasso (bool);
extern int picasso_display_mode_index (uae_u32 x, uae_u32 y, uae_u32 d);
extern int picasso_nr_resolutions (void);
extern void picasso_clip_mouse (int *, int *);

extern int NDX_InvertRect(struct RenderInfo* ri, unsigned long X, unsigned long Y, unsigned long Width, unsigned long Height, uae_u32 mask, int Bpp);
extern int NDX_BlitPattern(struct RenderInfo* ri,struct Pattern* pat,unsigned long X, unsigned long Y, unsigned long W, unsigned long H, uae_u8 Mask, uae_u32 RGBFmt);
extern int NDX_BlitTemplate(struct RenderInfo* ri, struct Template* tmp, unsigned long X, unsigned long Y, unsigned long W, unsigned long H, uae_u16 Mask);
extern int NDX_BlitPlanar2Chunky(struct RenderInfo* ri, struct BitMap* bm, unsigned long srcx, unsigned long srcy, unsigned long dstx, unsigned long dsty, unsigned long width, unsigned long height, uae_u8 minterm, uae_u8 mask);
extern int NDX_BlitPlanar2Direct(struct RenderInfo* ri, struct BitMap* bm, unsigned long srcx, unsigned long srcy, unsigned long dstx, unsigned long dsty, unsigned long width, unsigned long height, uae_u8 minterm, uae_u8 Mask);
extern int NDX_FillRect(struct RenderInfo* ri, unsigned long X, unsigned long Y, unsigned long Width, unsigned long Height, uae_u32 Pen, uae_u8 Mask, uae_u32 RGBFormat);
extern int NDX_BlitRect(struct RenderInfo* ri, unsigned long srcx, unsigned long srcy, unsigned long dstx, unsigned long dsty, unsigned long width, unsigned long height, uae_u8 Mask);
extern int NDX_BlitRectNoMaskComplete(struct RenderInfo* sri,struct RenderInfo* dri, unsigned long srcx, unsigned long srcy, unsigned long dstx, unsigned long dsty, unsigned long width, unsigned long height, uae_u8 OpCode, uae_u32 RGBFmt);

extern int picasso_is_special;
extern int picasso_is_special_read;

extern int p96hack_vpos2;
extern int p96refresh_active;
#endif

#endif

#endif /* UAE_PICASSO96_H */
