#include "raylib.h"
#include "app/game_app.h"
#include "audio/audio_manager.h"
#include "config/config.h"
#include "assets/game_assets.h"

int main() {
    InitWindow(AppConfig::WINDOW_WIDTH, AppConfig::WINDOW_HEIGHT, AppConfig::WINDOW_TITLE);
    SetExitKey(KEY_NULL);
    SetTargetFPS(AppConfig::TARGET_FPS);

    audio_manager_init();
    game_assets_load();

    GameAppState app;
    game_app_init(app);

    // game loop 
    while (!WindowShouldClose() && !app.shouldQuit) {
        audio_manager_update();
        game_app_update(app);

        BeginDrawing();
            game_app_draw(app);
            // meo :>
        EndDrawing();
    }

    game_assets_unload();
    audio_manager_shutdown();

    CloseWindow();
    return 0;
}