#include "overlays/overlay_pause.h"

#include "raylib.h"
#include "app/game_app.h"
#include "assets/game_assets.h"
#include "render/theme.h"
#include "overlays/overlay_common.h"
#include "screens/screens.h"
#include "ui/ui.h"

namespace {

    constexpr int BTN_RESUME_ID = 1;
    constexpr int BTN_MENU_ID = 2;
    constexpr int BTN_SETTING_ID = 3;


    Rectangle BTN_RESUME = {490, 300, 300, 70};
    Rectangle BTN_MENU   = {490, 400, 300, 70};
    Rectangle BTN_SETTING = {830, 205, 58, 58};

    void _draw_icon_button(
        int buttonId,
        Rectangle rect,
        const UIButtonStateTextures& textures,
        const char* fallbackText,
        float fallbackFontSize
    ) {
        const UIButtonState state = ui_button_get_state(buttonId, rect);
        if (ui_button_has_any_textures(textures)) {
            ui_button_draw_state_textures(rect, textures, state, false);
            return;
        }

        overlay_draw_button(buttonId, rect, fallbackText, fallbackFontSize);
    }

}

void overlay_pause_update(GameAppState& app) {

    if (ui_button_is_clicked(BTN_RESUME_ID, BTN_RESUME) || IsKeyPressed(KEY_R) || IsKeyPressed(KEY_ESCAPE)) {
        app.currentOverlay = APP_OVERLAY_NONE;
        return;
    }

    if (ui_button_is_clicked(BTN_MENU_ID, BTN_MENU) || IsKeyPressed(KEY_M)) {
        game_app_open_confirm_exit(app, EXIT_TARGET_PLAY_TO_MAIN_MENU);
        
        return;
    }

    if (ui_button_is_clicked(BTN_SETTING_ID, BTN_SETTING)) {
        app.currentOverlay = APP_OVERLAY_NONE;
        app.settingsReturnScreen = APP_SCREEN_PLAY;
        app.currentScreen = APP_SCREEN_SETTINGS;
        return;
    }
}

void overlay_pause_draw() {
    overlay_draw_backdrop(0.55f);

    Rectangle panel = {360, 180, 560, 360};
    overlay_draw_panel(panel, ui_color_overlay_panel_fill(), THEME_ACCENT_COLOR);

    const char* textTitle = u8"TẠM DỪNG";
    ui_draw_text_in_rect(
        g_assets.fonts.common,
        textTitle,
        panel,
        44.0f,
        1.0f,
        0.5f,
        0.1f,
        THEME_ACCENT_COLOR
    );

    overlay_draw_button(
        BTN_RESUME_ID,
        BTN_RESUME,
        u8"TIẾP TỤC",
        26.0f
    );

    overlay_draw_button(
        BTN_MENU_ID,
        BTN_MENU,
        u8"VỀ MENU CHÍNH",
        26.0f
    );

    _draw_icon_button(
        BTN_SETTING_ID,
        BTN_SETTING,
        g_assets.buttons.setting,
        u8"CÀI ĐẶT",
        14.0f
    );
}
