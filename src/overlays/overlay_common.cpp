#include "overlays/overlay_common.h"

#include "assets/game_assets.h"
#include "ui/ui.h"

void overlay_draw_backdrop(float alpha) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, alpha));
}

void overlay_draw_panel(
    Rectangle panel,
    Color fillColor,
    Color borderColor,
    float roundness,
    int segments,
    float borderThickness
) {
    DrawRectangleRounded(panel, roundness, segments, fillColor);
    DrawRectangleRoundedLinesEx(panel, roundness, segments, borderThickness, borderColor);
}

void overlay_draw_button(
    int buttonId,
    Rectangle rect,
    const char* text,
    float fontSize,
    bool isSelected
) {
    const UIButtonState state = ui_button_get_state(buttonId, rect);

    if (ui_button_has_any_textures(g_assets.buttons.common)) {
        ui_button_draw_state_textures(rect, g_assets.buttons.common, state, isSelected);
    } else {
        ui_button_draw(rect, UI_BUTTON_STYLE_COMMON, state);
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
