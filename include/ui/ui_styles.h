#pragma once

#include "ui/ui_button.h"
#include "ui/ui_text_input.h"

inline const UIButtonStyle UI_BUTTON_STYLE_COMMON = {GRAY, BLUE, GREEN, BLACK};
inline const UIButtonStyle UI_BUTTON_STYLE_DISABLED = {LIGHTGRAY, LIGHTGRAY, GRAY, DARKGRAY};


UITextInputStyle ui_style_text_input_common();

Color ui_color_panel_fill();
Color ui_color_overlay_panel_fill();

inline const Color UI_COLOR_TEXT_MUTED = LIGHTGRAY;
inline const Color UI_COLOR_LABEL = RAYWHITE;

inline const Color UI_COLOR_SWITCH_ON = GREEN;
inline const Color UI_COLOR_SWITCH_ON_PRESSED = LIME;
inline const Color UI_COLOR_SWITCH_OFF = GRAY;

inline const Color UI_COLOR_FRAME = DARKGRAY;
