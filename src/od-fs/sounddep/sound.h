 /*
  * UAE - The Un*x Amiga Emulator
  *
  * Support for SDL sound
  *
  * Copyright 1997 Bernd Schmidt
  */

#define SOUNDSTUFF 1

#include "fsemu-audiobuffer.h"
#define AUDIO_NAME "fsuae"

extern uae_u16 paula_sndbuffer[];
extern uae_u16 *paula_sndbufpt;
extern int paula_sndbufsize;
extern void finish_sound_buffer (void);
extern void restart_sound_buffer (void);
extern void pause_sound_buffer (void);
extern int init_sound (void);
extern void close_sound (void);
extern int setup_sound (void);
extern void resume_sound (void);
extern void pause_sound (void);
extern void reset_sound (void);
extern void sound_setadjust (double);

extern int drivesound_init (void);
extern void drivesound_free (void);
extern void sound_mute (int);
extern void sound_volume (int);
extern void set_volume (int, int);
extern void master_sound_volume (int);

extern int active_sound_stereo;

#define PUT_SOUND_WORD(b) do { *(uae_u16 *)paula_sndbufpt = b; paula_sndbufpt = (uae_u16 *)(((uae_u8 *)paula_sndbufpt) + 2); } while (0)
#define PUT_SOUND_WORD_LEFT(b) do { if (currprefs.sound_filter) b = filter (b, &sound_filter_state[0]); PUT_SOUND_WORD(b); } while (0)
// #define PUT_SOUND_WORD_RIGHT(b) do { if (currprefs.sound_filter) b = filter (b, &sound_filter_state[1]); PUT_SOUND_WORD(b); } while (0)
// #define PUT_SOUND_WORD_LEFT2(b) do { if (currprefs.sound_filter) b = filter (b, &sound_filter_state[2]); PUT_SOUND_WORD(b); } while (0)
// #define PUT_SOUND_WORD_RIGHT2(b) do { if (currprefs.sound_filter) b = filter (b, &sound_filter_state[3]); PUT_SOUND_WORD(b); } while (0)

#define PUT_SOUND_WORD_MONO(b) PUT_SOUND_WORD_LEFT(b)
#define SOUND16_BASE_VAL 0
#define SOUND8_BASE_VAL 128

#define DEFAULT_SOUND_MAXB 16384
// #define DEFAULT_SOUND_MINB 16384
// #define DEFAULT_SOUND_BITS 16
#define DEFAULT_SOUND_FREQ 44100
#define HAVE_STEREO_SUPPORT

#define FILTER_SOUND_OFF 0
#define FILTER_SOUND_EMUL 1
#define FILTER_SOUND_ON 2

#define FILTER_SOUND_TYPE_A500 0
#define FILTER_SOUND_TYPE_A1200 1
#define FILTER_SOUND_TYPE_A500_FIXEDONLY 2

#define FILTER_SOUND_TYPE_A500 0
#define FILTER_SOUND_TYPE_A1200 1
