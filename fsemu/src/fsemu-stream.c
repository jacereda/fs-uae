#define FSEMU_INTERNAL
#include "fsemu-stream.h"
#include <stdlib.h>

// typedef SDL_RWops fsemu_stream_t;

static void fsemu_stream_free(fsemu_stream_t *stream)
{
    printf("fsemu_stream_free stream=%p\n", stream);
#if defined FSEMU_SDL
    if (stream->rwops) {
        SDL_FreeRW(stream->rwops);
    }
#endif
    free(stream);
}

static void fsemu_stream_cleanup(void *stream)
{
    fsemu_stream_free((fsemu_stream_t *) stream);
}

#if defined FSEMU_SDL
static fsemu_stream_t *fsemu_stream_new_with_rwops(SDL_RWops *rwops)
{
    fsemu_stream_t *stream = malloc(sizeof(fsemu_stream_t));
    printf("fsemu_stream_new_with_rwops rwops=%p -> %p\n", rwops, stream);
    stream->rwops = rwops;
    fsemu_refable_set_cleanup_handler(stream, fsemu_stream_cleanup);
    return stream;
}
#endif

fsemu_stream_t *fsemu_stream_null(void)
{
#if defined FSEMU_SDL
    return fsemu_stream_new_with_rwops(NULL);

    // We should probably not need any actual data since size is 0, but
    // could be nice to use a "real pointer" to avoid confusing tools?
    // FIXME: Could re-use a global null stream object and just ref it.

    // static int null_data;
    // return fsemu_stream_from_const_data(&null_data, 0);
#else
    fsemu_stream_t *stream = malloc(sizeof(fsemu_stream_t));
    printf("fsemu_stream_null -> %p\n", stream);
    stream->rwops = NULL;
    fsemu_refable_set_cleanup_handler(stream, fsemu_stream_cleanup);
    return stream;
#endif
}

fsemu_stream_t *fsemu_stream_new(void)
{
#if defined FSEMU_SDL
    return fsemu_stream_new_with_rwops(SDL_AllocRW());
#else
    return fsemu_stream_null();
#endif
}

void fsemu_stream_unref(fsemu_stream_t *stream)
{
    printf("fsemu_stream_unref stream=%p\n", stream);
    fsemu_refable_unref(stream);
}

fsemu_stream_t *fsemu_stream_from_const_data(const void *mem, int size)
{
#if defined FSEMU_SDL
    return fsemu_stream_new_with_rwops(SDL_RWFromConstMem(mem, size));
#else
    return fsemu_stream_null();
#endif
}

fsemu_stream_t *fsemu_stream_from_file(FILE *fp, bool autoclose)
{
#if defined FSEMU_SDL
    return fsemu_stream_new_with_rwops(SDL_RWFromFP(fp, autoclose));
#else
    return fsemu_stream_null();
#endif
}

fsemu_stream_t *fsemu_stream_from_path(const char *file, const char *mode)
{
#if defined FSEMU_SDL
    return fsemu_stream_new_with_rwops(SDL_RWFromFile(file, mode));
#else
    return fsemu_stream_null();
#endif
}

fsemu_stream_t *fsemu_stream_from_data(void *mem, int size)
{
#if defined FSEMU_SDL
    return fsemu_stream_new_with_rwops(SDL_RWFromMem(mem, size));
#else
    return fsemu_stream_null();
#endif
}

// #define fsemu_stream_from_const_data SDL_RWFromConstMem
// #define fsemu_stream_from_file SDL_RWFromFP
// #define fsemu_stream_from_path SDL_RWFromFile
// #define fsemu_stream_from_data SDL_RWFromMem

int fsemu_stream_close(fsemu_stream_t *stream)
{
    if (stream->rwops == NULL) {
        return 0;
    }
#if defined FSEMU_SDL
    return SDL_RWclose(stream->rwops);
#else
    return 0;
#endif
}

int64_t fsemu_stream_size(fsemu_stream_t *stream)
{
    if (stream->rwops == NULL) {
        return 0;
    }
#if defined FSEMU_SDL
    return SDL_RWsize(stream->rwops);
#else
    return 0;
#endif
}

size_t fsemu_stream_read(fsemu_stream_t *stream,
                         void *ptr,
                         size_t size,
                         size_t maxnum)
{
    if (stream->rwops == NULL) {
        return 0;
    }
#if defined FSEMU_SDL
    return SDL_RWread(stream->rwops, ptr, size, maxnum);
#else
    return 0;
#endif
}

/*
#define fsemu_stream_seek SDL_RWseek
#define fsemu_stream_size SDL_RWsize
#define fsemu_stream_tell SDL_RWtell
#define fsemu_stream_write SDL_RWwrite

#define fsemu_stream_read_be16 SDL_ReadBE16
#define fsemu_stream_read_be32 SDL_ReadBE32
#define fsemu_stream_read_be64 SDL_ReadBE64
#define fsemu_stream_read_le16 SDL_ReadLE16
#define fsemu_stream_read_le32 SDL_ReadLE32
#define fsemu_stream_read_le64 SDL_ReadLE64
#define fsemu_stream_read_u8 SDL_ReadU8

#define fsemu_stream_write_be16 SDL_WriteBE16
#define fsemu_stream_write_be32 SDL_WriteBE32
#define fsemu_stream_write_be64 SDL_WriteBE64
#define fsemu_stream_write_le16 SDL_WriteLE16
#define fsemu_stream_write_le32 SDL_WriteLE32
#define fsemu_stream_write_le64 SDL_WriteLE64
#define fsemu_stream_write_u8 SDL_WriteU8
*/
