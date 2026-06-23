#include "screens/screen_settings.h"

#include <cstdio>

#include "app/game_app.h"
#include "assets/game_assets.h"
#include "raylib.h"
#include "render/theme.h"
#include "screens/screens.h"
#include "ui/ui.h"

namespace {
    constexpr int BTN_BACK_ID = 1;
    constexpr int BTN_MASTER_DEC_ID = 2;
    constexpr int BTN_MASTER_INC_ID = 3;
    constexpr int BTN_MUSIC_DEC_ID = 4;
    constexpr int BTN_MUSIC_INC_ID = 5;
    constexpr int BTN_MUSIC_TOGGLE_ID = 6;
    constexpr int BTN_SOUND_DEC_ID = 7;
    constexpr int BTN_SOUND_INC_ID = 8;
    constexpr int BTN_SOUND_TOGGLE_ID = 9;
    constexpr int BTN_HINT_YES_ID = 10;
    constexpr int BTN_HINT_NO_ID = 11;

    const Rectangle PANEL = {260, 82, 760, 500};
    const Rectangle TITLE_RECT = {260, 102, 760, 46};
    const Rectangle BTN_BACK = {540, 626, 200, 70};

    const Rectangle MASTER_LABEL = {330, 190, 270, 30};
    const Rectangle MASTER_DEC = {650, 182, 58, 58};
    const Rectangle MASTER_VALUE = {720, 190, 100, 36};
    const Rectangle MASTER_INC = {835, 182, 58, 58};

    const Rectangle MUSIC_LABEL = {330, 280, 270, 30};
    const Rectangle MUSIC_DEC = {650, 272, 58, 58};
    const Rectangle MUSIC_VALUE = {720, 280, 100, 36};
    const Rectangle MUSIC_INC = {835, 272, 58, 58};
    const Rectangle MUSIC_TOGGLE = {910, 272, 58, 58};

    const Rectangle SOUND_LABEL = {330, 370, 270, 30};
    const Rectangle SOUND_DEC = {650, 362, 58, 58};
    const Rectangle SOUND_VALUE = {720, 370, 100, 36};
    const Rectangle SOUND_INC = {835, 362, 58, 58};
    const Rectangle SOUND_TOGGLE = {910, 362, 58, 58};

    const Rectangle HINT_LABEL = {330, 468, 270, 30};
    const Rectangle HINT_YES = {690, 455, 58, 58};
    const Rectangle HINT_NO = {800, 455, 58, 58};

    bool g_selectedHintOption = false;

    int _clamp_percent(int value) {
        if (value < 0) return 0;
        if (value > 100) return 100;
        return value;
    }

    void _change_percent(int& value, int delta) {
        value = _clamp_percent(value + delta);
    }

    void _draw_value(Rectangle rect, int value) {
        char text[16];
        std::snprintf(text, sizeof(text), "%d%%", value);
        ui_draw_text_in_rect(
            g_assets.fonts.common,
            text,
            rect,
            24.0f,
            1.0f,
            0.5f,
            0.5f,
            THEME_TEXT_COLOR
        );
    }

    void _draw_label(Rectangle rect, const char* text) {
        ui_draw_text_in_rect(
            g_assets.fonts.common,
            text,
            rect,
            24.0f,
            1.0f,
            0.0f,
            0.5f,
            THEME_TEXT_COLOR
        );
    }

    void _draw_icon_button(
        int buttonId,
        Rectangle rect,
        const UIButtonStateTextures& textures,
        const char* fallbackText,
        float fallbackFontSize,
        bool isSelected = false
    ) {
        const UIButtonState state = ui_button_get_state(buttonId, rect);
        if (ui_button_has_any_textures(textures)) {
            ui_button_draw_state_textures_tinted(rect, textures, state, isSelected, GRAY);
            return;
        }

        screen_draw_button(buttonId, rect, fallbackText, fallbackFontSize);
    }
}

void screen_settings_update(GameAppState& app) {
    bool changedAudio = false;

    if (ui_button_is_clicked(BTN_MASTER_DEC_ID, MASTER_DEC)) {
        _change_percent(app.settings.masterVolumePercent, -5);
        changedAudio = true;
    }
    if (ui_button_is_clicked(BTN_MASTER_INC_ID, MASTER_INC)) {
        _change_percent(app.settings.masterVolumePercent, 5);
        changedAudio = true;
    }

    if (ui_button_is_clicked(BTN_MUSIC_DEC_ID, MUSIC_DEC)) {
        _change_percent(app.settings.musicVolumePercent, -5);
        changedAudio = true;
    }
    if (ui_button_is_clicked(BTN_MUSIC_INC_ID, MUSIC_INC)) {
        _change_percent(app.settings.musicVolumePercent, 5);
        changedAudio = true;
    }
    if (ui_button_is_clicked(BTN_MUSIC_TOGGLE_ID, MUSIC_TOGGLE)) {
        app.settings.musicMuted = !app.settings.musicMuted;
        changedAudio = true;
    }

    if (ui_button_is_clicked(BTN_SOUND_DEC_ID, SOUND_DEC)) {
        _change_percent(app.settings.soundVolumePercent, -5);
        changedAudio = true;
    }
    if (ui_button_is_clicked(BTN_SOUND_INC_ID, SOUND_INC)) {
        _change_percent(app.settings.soundVolumePercent, 5);
        changedAudio = true;
    }
    if (ui_button_is_clicked(BTN_SOUND_TOGGLE_ID, SOUND_TOGGLE)) {
        app.settings.soundMuted = !app.settings.soundMuted;
        changedAudio = true;
    }

    if (ui_button_is_clicked(BTN_HINT_YES_ID, HINT_YES)) {
        app.settings.hintsEnabled = true;
        g_selectedHintOption = true;
    }
    if (ui_button_is_clicked(BTN_HINT_NO_ID, HINT_NO)) {
        app.settings.hintsEnabled = false;
        g_selectedHintOption = false;
    }

    if (changedAudio) {
        game_app_apply_audio_settings(app);
    }

    if (ui_button_is_clicked(BTN_BACK_ID, BTN_BACK) || IsKeyPressed(KEY_ESCAPE)) {
        app.currentScreen = app.settingsReturnScreen;
        app.currentOverlay = APP_OVERLAY_NONE;
    }
}

void screen_settings_draw(const GameAppState& app) {
    ClearBackground(THEME_BG_COLOR);

    screen_draw_background(g_assets.images.bg_setting, BLACK);
    DrawRectangleRounded(PANEL, 0.06f, 8, ui_color_panel_fill());
    DrawRectangleRoundedLinesEx(PANEL, 0.06f, 8, 3.0f, THEME_ACCENT_COLOR);

    ui_draw_text_in_rect_with_outline(
        g_assets.fonts.common,
        u8"CÀI ĐẶT",
        TITLE_RECT,
        42.0f,
        1.0f,
        0.5f,
        0.5f,
        2.0f,
        THEME_ACCENT_COLOR,
        BLACK
    );

    _draw_label(MASTER_LABEL, u8"Âm lượng chính");
    _draw_icon_button(BTN_MASTER_DEC_ID, MASTER_DEC, g_assets.buttons.decrease, "-", 30.0f);
    _draw_value(MASTER_VALUE, app.settings.masterVolumePercent);
    _draw_icon_button(BTN_MASTER_INC_ID, MASTER_INC, g_assets.buttons.increase, "+", 30.0f);

    _draw_label(MUSIC_LABEL, u8"Âm lượng nhạc");
    _draw_icon_button(BTN_MUSIC_DEC_ID, MUSIC_DEC, g_assets.buttons.music_decrease, "-", 30.0f);
    _draw_value(MUSIC_VALUE, app.settings.musicVolumePercent);
    _draw_icon_button(BTN_MUSIC_INC_ID, MUSIC_INC, g_assets.buttons.music_increase, "+", 30.0f);
    _draw_icon_button(
        BTN_MUSIC_TOGGLE_ID,
        MUSIC_TOGGLE,
        app.settings.musicMuted ? g_assets.buttons.music_off : g_assets.buttons.music_on,
        app.settings.musicMuted ? "OFF" : "ON",
        18.0f
    );

    _draw_label(SOUND_LABEL, u8"Âm lượng hiệu ứng");
    _draw_icon_button(BTN_SOUND_DEC_ID, SOUND_DEC, g_assets.buttons.sound_decrease, "-", 30.0f);
    _draw_value(SOUND_VALUE, app.settings.soundVolumePercent);
    _draw_icon_button(BTN_SOUND_INC_ID, SOUND_INC, g_assets.buttons.sound_increase, "+", 30.0f);
    _draw_icon_button(
        BTN_SOUND_TOGGLE_ID,
        SOUND_TOGGLE,
        app.settings.soundMuted ? g_assets.buttons.sound_off : g_assets.buttons.sound_on,
        app.settings.soundMuted ? "OFF" : "ON",
        18.0f
    );

    _draw_label(HINT_LABEL, u8"Gợi ý trong game");
    _draw_icon_button(BTN_HINT_YES_ID, HINT_YES, g_assets.buttons.yes, "YES", 18.0f, !g_selectedHintOption);
    _draw_icon_button(BTN_HINT_NO_ID, HINT_NO, g_assets.buttons.no, "NO", 18.0f, g_selectedHintOption);

    screen_draw_button(BTN_BACK_ID, BTN_BACK, u8"QUAY LẠI", 28.0f);
}
