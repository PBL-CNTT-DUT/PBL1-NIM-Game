#include "ui/ui_layout.h"


Vector2 ui_text_position_in_rect(
    Rectangle rect,
    Font font,
    const char* text,
    float fontSize,
    float spacing,
    float alignX,
    float alignY
) {
    if (text == nullptr) {
        text = "";
    }

    const Vector2 textSize = MeasureTextEx(font, text, fontSize, spacing);

    return Vector2{
        rect.x + (rect.width - textSize.x) * alignX,
        rect.y + (rect.height - textSize.y) * alignY
    };
}


Rectangle ui_rect_in_rect(Rectangle outer, float width, float height, float alignX, float alignY) {
    return Rectangle{
        outer.x + (outer.width  - width)  * alignX,
        outer.y + (outer.height - height) * alignY,
        width,
        height
    };
}


void ui_draw_rect_in_rect(Rectangle outer, float width, float height, float alignX, float alignY, Color color, float roundness, int segments) {
    const Rectangle inner = ui_rect_in_rect(outer, width, height, alignX, alignY);
    if (roundness > 0.0f) {
        DrawRectangleRounded(inner, roundness, segments, color);
    } else {
        DrawRectangleRec(inner, color);
    }
}

void ui_draw_texture_in_rect(Texture2D texture, Rectangle rect, Color tint) {
    if (texture.id == 0) {
        return;
    }

    const Rectangle src = {0.0f, 0.0f, (float)texture.width, (float)texture.height};
    DrawTexturePro(texture, src, rect, Vector2{0.0f, 0.0f}, 0.0f, tint);
}

