#include "screens/screen_help.h"

#include "app/game_app.h"
#include "assets/game_assets.h"
#include "raylib.h"
#include "render/theme.h"
#include "screens/screens.h"
#include "ui/ui.h"

namespace {
    constexpr int BTN_BACK_ID = 1;

    Rectangle BTN_BACK = {540, 626, 200, 70};

    void _draw_section_panel(Rectangle panel, const char* title) {
        DrawRectangleRounded(panel, 0.07f, 8, ui_color_panel_fill());
        DrawRectangleRoundedLinesEx(panel, 0.07f, 8, 1.5f, UI_COLOR_FRAME);

        ui_draw_text_in_rect_with_outline(
            g_assets.fonts.common,
            title,
            Rectangle{panel.x, panel.y + 10.0f, panel.width, 32.0f},
            24.0f, 1.0f, 0.5f, 0.5f, 1.5f,
            THEME_ACCENT_COLOR, BLACK
        );

        DrawLineEx(
            Vector2{panel.x + 20.0f, panel.y + 48.0f},
            Vector2{panel.x + panel.width - 20.0f, panel.y + 48.0f},
            1.0f,
            UI_COLOR_FRAME
        );
    }

} // namespace







// * ---------------------------------------------------------------------



void screen_help_update(GameAppState& app) {
    if (ui_button_is_clicked(BTN_BACK_ID, BTN_BACK) || IsKeyPressed(KEY_ESCAPE)) {
        app.currentScreen = APP_SCREEN_MAIN_MENU;
    }
}

void screen_help_draw() {
    ClearBackground(THEME_BG_COLOR);

    screen_draw_background(g_assets.images.bg_help, BLACK);

    const float W = (float)GetScreenWidth();

    ui_draw_text_in_rect_with_outline(
        g_assets.fonts.common,
        u8"HƯỚNG DẪN",
        Rectangle{0.0f, 22.0f, W, 52.0f},
        48.0f, 1.0f, 0.5f, 0.5f, 2.0f,
        THEME_TEXT_COLOR, BLACK
    );

    const Rectangle leftPanel  = {36.0f, 96.0f, 576.0f, 510.0f};
    _draw_section_panel(leftPanel, u8"VỀ TRÒ CHƠI NIM");

    DrawTextEx(
        g_assets.fonts.common,
        u8"NIM là trò chơi chiến thuật toán học cổ điển.\n\n"
        u8"Có nhiều cụm đá trên bàn. Hai người chơi\n"
        u8"thay nhau lấy đá từ một cụm bất kỳ.\n\n"
        u8"LUẬT BỐC CUỐI THUA:\n"
        u8"  Người lấy viên đá cuối cùng THUA.\n\n"
        u8"LUẬT BỐC CUỐI THẮNG:\n"
        u8"  Người lấy viên đá cuối cùng THẮNG.\n\n"
        u8"GIỚI HẠN BỐC:\n"
        u8"  Mỗi lượt chỉ được lấy tối đa N viên\n"
        u8"  (tùy cài đặt trận đấu).\n\n"
        u8"MẸO CHIẾN THUẬT:\n"
        u8"  NIM có nước đi tối ưu tính bằng XOR\n"
        u8"  của các cụm đá (Nim-value = 0 là thế thua).",
        Vector2{leftPanel.x + 20.0f, leftPanel.y + 56.0f},
        g_assets.fonts.common.baseSize > 0 ? 19.0f : 19.0f,
        1.0f,
        THEME_TEXT_COLOR
    );

    const Rectangle rightPanel = {632.0f, 96.0f, 612.0f, 510.0f};
    _draw_section_panel(rightPanel, u8"CÁCH CHƠI & ĐIỀU KHIỂN");

    DrawTextEx(
        g_assets.fonts.common,
        u8"1. CHỌN ĐÁ:\n"
        u8"   Click vào đám mây trong cụm đá.\n"
        u8"   (Bốc từ viên đầu đến vị trí đó)\n\n"
        u8"2. XÁC NHẬN NƯỚC ĐI:\n"
        u8"   Nhấn nút ĐỒNG Ý hoặc phím Enter.\n\n"
        u8"3. THAY ĐỔI LỰA CHỌN:\n"
        u8"   Click vào đám mây khác để chọn lại.\n\n"
        u8"4. NÚT GỢI Ý:\n"
        u8"   Sáng lên khi tới lượt bạn. Nhấn để AI\n"
        u8"   tự chọn nước tối ưu — bạn vẫn cần\n"
        u8"   xác nhận bằng ĐỒNG Ý hoặc Enter.\n\n"
        u8"5. TẠM DỪNG:\n"
        u8"   Nhấn ESC trong khi chơi.\n\n"
        u8"6. ĐỘ KHÓ AI:\n"
        u8"   Very Easy → dễ nhất (random hoàn toàn)\n"
        u8"   Very Hard → khó nhất (100% tối ưu)",
        Vector2{rightPanel.x + 20.0f, rightPanel.y + 56.0f},
        19.0f,
        1.0f,
        THEME_TEXT_COLOR
    );

    
    screen_draw_button(BTN_BACK_ID, BTN_BACK, u8"QUAY LẠI", 36.0f);
}
