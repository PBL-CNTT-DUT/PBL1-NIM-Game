#pragma once

#include "raylib.h"

void screen_draw_background(Color fallbackColor);
void screen_draw_background(Texture2D texture, Color fallbackColor);
void screen_draw_button(
    int buttonId,
    Rectangle rect,
    const char* text,
    float fontSize,
    bool isSelected = false
);
void screen_draw_disabled_button(
    int buttonId,
    Rectangle rect,
    const char* text,
    float fontSize,
    bool isSelected = false
);
