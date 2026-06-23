#pragma once

#include "raylib.h"

Vector2 ui_text_position_in_rect(
    Rectangle rect,
    Font font,
    const char* text,
    float fontSize,
    float spacing = 1.0f,
    float alignX = 0.5f,
    float alignY = 0.5f
);


// alignX/Y: 0.0=trái/trên, 0.5=giữa, 1.0=phải/dưới
Rectangle ui_rect_in_rect(
    Rectangle outer,
    float width,
    float height,
    float alignX = 0.5f,
    float alignY = 0.5f
);


// roundness=0 → góc vuông; roundness>0 → góc tròn (dùng DrawRectangleRounded).
void ui_draw_rect_in_rect(
    Rectangle outer,
    float width,
    float height,
    float alignX,
    float alignY,
    Color color,
    float roundness = 0.0f,
    int   segments  = 8
);

void ui_draw_texture_in_rect(
    Texture2D texture,
    Rectangle rect,
    Color tint = WHITE
);
