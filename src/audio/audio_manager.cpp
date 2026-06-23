#include "audio/audio_manager.h"

#include "assets/game_assets.h"
#include "raylib.h"

void audio_manager_init() {
    if (!IsAudioDeviceReady()) {
        InitAudioDevice();
    }
}

void audio_manager_update() {
    if (IsAudioDeviceReady() && g_assets.musics.bgm.frameCount > 0) {
        UpdateMusicStream(g_assets.musics.bgm);
    }
}

void audio_manager_shutdown() {
    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }
}
