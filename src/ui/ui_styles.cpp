#include "ui/ui_styles.h"

#include "render/theme.h"

UITextInputStyle ui_style_text_input_common() {
    return UITextInputStyle{
        DARKGRAY,
        GRAY,
        GRAY,
        THEME_ACCENT_COLOR,
        RAYWHITE,
        LIGHTGRAY
    };
}



Color ui_color_overlay_panel_fill() {
    return ColorAlpha(BLACK, 0.90f);
}

Color ui_color_panel_fill() {
    return ui_color_overlay_panel_fill();
}
