#pragma once

#include "raylib.h"

void overlay_draw_backdrop(float alpha);
void overlay_draw_panel(
    Rectangle panel,
    Color fillColor,
    Color borderColor,
    float roundness = 0.08f,
    int segments = 8,
    float borderThickness = 3.0f
);
void overlay_draw_button(
    int buttonId,
    Rectangle rect,
    const char* text,
    float fontSize,
    bool isSelected = false
);
