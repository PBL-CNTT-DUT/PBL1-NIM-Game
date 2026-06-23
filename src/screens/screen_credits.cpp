#include "screens/screen_credits.h"

#include "raylib.h"
#include "app/game_app.h"
#include "assets/game_assets.h"
#include "render/theme.h"
#include "screens/screens.h"
#include "ui/ui.h"

namespace {
    constexpr int BTN_BACK_ID = 1;

    Rectangle BTN_BACK = {540, 600, 200, 75};

} // 


void screen_credits_update(GameAppState& app) {
    if (ui_button_is_clicked(BTN_BACK_ID, BTN_BACK) || IsKeyPressed(KEY_ESCAPE)) {
        app.currentScreen = APP_SCREEN_MAIN_MENU;
    }
}

void screen_credits_draw() {
    screen_draw_background(THEME_BG_COLOR);

    const Rectangle screenRect = {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()};

    ui_draw_text_in_rect_with_outline(
        g_assets.fonts.common,
        u8"THÔNG TIN",
        screenRect,
        52.0f,
        1.0f,
        0.5f,
        0.25f,
        2.0f,
        THEME_TEXT_COLOR,
        BLACK
    );

    ui_draw_text_in_rect(
        g_assets.fonts.common,
        u8"Credits screen\nTạ Anh Tuấn\nTôn Nguyễn Khánh Huyền",
        screenRect,
        28.0f,
        1.0f,
        0.5f,
        0.45f,
        THEME_ACCENT_COLOR
    );

    ui_draw_text_in_rect(
        g_assets.fonts.common,
        u8"ESC để quay lại",
        screenRect,
        24.0f,
        1.0f,
        0.5f,
        0.58f,
        THEME_TEXT_COLOR
    );

    screen_draw_button(BTN_BACK_ID, BTN_BACK, u8"QUAY LẠI", 36);

}
