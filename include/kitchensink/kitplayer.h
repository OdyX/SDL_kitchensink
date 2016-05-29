#ifndef KITPLAYER_H
#define KITPLAYER_H

#include "kitchensink/kitsource.h"
#include "kitchensink/kitconfig.h"
#include "kitchensink/kitformats.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_thread.h>
#include <SDL2/SDL_surface.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Kit_DecoderThread Kit_DecoderThread;
typedef struct Kit_DemuxThread Kit_DemuxThread;

#define KIT_CODECMAX 16
#define KIT_CODECNAMEMAX 128

enum {
    THREAD_AUDIO = 0,
    THREAD_VIDEO,
    THREAD_SUBTITLE,
    NB_THREAD_TYPES
};

typedef enum Kit_PlayerState {
    KIT_STOPPED = 0, ///< Playback stopped or has not started yet.
    KIT_PLAYING, ///< Playback started & player is actively decoding.
    KIT_PAUSED, ///< Playback paused; player is actively decoding but no new data is given out.
    KIT_CLOSED ///< Playback is stopped and player is closing.
} Kit_PlayerState;

typedef struct Kit_Player {
    Kit_PlayerState state; ///< Playback state
    double clock_sync; ///< Clock sync point
    double pause_start; ///< Timestamp of pause beginning
    const Kit_Source *src; ///< Reference to Audio/Video source
    Kit_DecoderThread *dec_threads[NB_THREAD_TYPES]; // All decoder threads
    Kit_DemuxThread *demux_thread; // demuxer thread
} Kit_Player;

typedef struct Kit_PlayerInfo {
    char acodec[KIT_CODECMAX]; ///< Audio codec short name, eg "ogg", "mp3"
    char acodec_name[KIT_CODECNAMEMAX]; ///< Audio codec long, more descriptive name
    char vcodec[KIT_CODECMAX]; ///< Video codec short name, eg. "x264"
    char vcodec_name[KIT_CODECNAMEMAX]; ///< Video codec long, more descriptive name
    char scodec[KIT_CODECMAX]; ///< Subtitle codec short name, eg. "ass"
    char scodec_name[KIT_CODECNAMEMAX]; ///< Subtitle codec long, more descriptive name
    Kit_VideoFormat video; ///< Video format information
    Kit_AudioFormat audio; ///< Audio format information
    Kit_SubtitleFormat subtitle; ///< Subtitle format information
} Kit_PlayerInfo;

KIT_API Kit_Player* Kit_CreatePlayer(const Kit_Source *src);
KIT_API void Kit_ClosePlayer(Kit_Player *player);

KIT_API int Kit_GetVideoData(Kit_Player *player, SDL_Texture *texture);
KIT_API int Kit_GetSubtitleData(Kit_Player *player, SDL_Renderer *renderer);
KIT_API int Kit_GetAudioData(Kit_Player *player, unsigned char *buffer, int length, int cur_buf_len);
KIT_API void Kit_GetPlayerInfo(const Kit_Player *player, Kit_PlayerInfo *info);

KIT_API Kit_PlayerState Kit_GetPlayerState(const Kit_Player *player);
KIT_API void Kit_PlayerPlay(Kit_Player *player);
KIT_API void Kit_PlayerStop(Kit_Player *player);
KIT_API void Kit_PlayerPause(Kit_Player *player);

KIT_API int Kit_PlayerSeek(Kit_Player *player, double time);
KIT_API double Kit_GetPlayerDuration(const Kit_Player *player);
KIT_API double Kit_GetPlayerPosition(const Kit_Player *player);

#ifdef __cplusplus
}
#endif

#endif // KITPLAYER_H
