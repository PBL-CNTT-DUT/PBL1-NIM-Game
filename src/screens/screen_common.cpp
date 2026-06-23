#include "screens/screen_common.h"

#include "assets/game_assets.h"
#include "ui/ui.h"

namespace {
    void _draw_button_with_style(
        int buttonId,
        Rectangle rect,
        const char* text,
        float fontSize,
        const UIButtonStyle& style,
        bool isSelected
    ) {
        const UIButtonState state = ui_button_get_state(buttonId, rect);

        if (ui_button_has_any_textures(g_assets.buttons.common)) {
            ui_button_draw_state_textures(rect, g_assets.buttons.common, state, isSelected);
        } else {
            ui_button_draw(rect, style, state);
        }

        ui_button_draw_text(
            rect,
            text,
            g_assets.fonts.common,
            fontSize,
            state,
            DARKGRAY,
            BLACK,
            WHITE
        );
    }
}

void screen_draw_background(Color fallbackColor) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fallbackColor);
}

void screen_draw_background(Texture2D texture, Color fallbackColor) {
    if (texture.id != 0) {
        const Rectangle dst = {0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight()};
        ui_draw_texture_in_rect(texture, dst);
        return;
    }

    screen_draw_background(fallbackColor);
}

void screen_draw_button(
    int buttonId,
    Rectangle rect,
    const char* text,
    float fontSize,
    bool isSelected
) {
    _draw_button_with_style(buttonId, rect, text, fontSize, UI_BUTTON_STYLE_COMMON, isSelected);
}

void screen_draw_disabled_button(
    int buttonId,
    Rectangle rect,
    const char* text,
    float fontSize,
    bool isSelected
) {
    _draw_button_with_style(buttonId, rect, text, fontSize, UI_BUTTON_STYLE_DISABLED, isSelected);
}
