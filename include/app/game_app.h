#pragma once

#include "game/game_settings.h"

enum AppScreen {
    APP_SCREEN_MAIN_MENU = 0,
    APP_SCREEN_MATCH_SETUP,
    APP_SCREEN_HELP,
    APP_SCREEN_CREDITS,
    APP_SCREEN_SETTINGS,
    APP_SCREEN_PLAY
};

enum AppOverlay {
    APP_OVERLAY_NONE = 0,
    APP_OVERLAY_PAUSE,
    APP_OVERLAY_RESULT,
    APP_OVERLAY_CONFIRM_EXIT
};

enum ExitTarget {
    EXIT_TARGET_NONE = 0,
    EXIT_TARGET_APP,
    EXIT_TARGET_PLAY_TO_MAIN_MENU
};

enum MatchSetupStep {
    MATCH_SETUP_STEP_MODE = 0,
    MATCH_SETUP_STEP_DIFFICULTY,
    MATCH_SETUP_STEP_NAMES,
    MATCH_SETUP_STEP_ROUND_SETUP,
};

struct MatchSetupState {
    MatchSetupStep step = MATCH_SETUP_STEP_MODE;
    GameMode gameMode = GAME_MODE_PVAI;
    AIDifficulty difficulty = AI_DIFFICULTY_MEDIUM;
    char playerNames[2][32] = {u8"Người chơi 1", u8"Người chơi 2"};
    int activeNameInput = -1;
    GameRule gameRule = GAME_RULE_LAST_TAKE_LOSE;
    bool useTakeLimit = false;
    int takeLimit = 3;
    int pileCount = 3;
};

struct AppSettingsState {
    int masterVolumePercent = 100;
    int musicVolumePercent = 10;
    int soundVolumePercent = 55;
    bool musicMuted = false;
    bool soundMuted = false;
    bool hintsEnabled = true;
};

struct GameAppState {
    AppScreen currentScreen = APP_SCREEN_MAIN_MENU;
    AppOverlay currentOverlay = APP_OVERLAY_NONE;
    AppScreen settingsReturnScreen = APP_SCREEN_MAIN_MENU;
    ExitTarget exitTarget = EXIT_TARGET_NONE;
    bool shouldQuit = false;

    GameSettings gameSettings{};
    AppSettingsState settings{};
    // Draft cau hinh truoc tran; game runtime nam trong screen_play.
    MatchSetupState setup{};

    char resultMessage[96] = "";
};

void game_app_init(GameAppState& app);
void game_app_update(GameAppState& app);
void game_app_draw(const GameAppState& app);

void game_app_reset_match_setup(GameAppState& app);
void game_app_show_result(GameAppState& app, const char* message);
void game_app_open_confirm_exit(GameAppState& app, ExitTarget target);
void game_app_apply_audio_settings(const GameAppState& app);
