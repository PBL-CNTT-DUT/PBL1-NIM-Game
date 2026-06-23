#include "ui/ui_button.h"

#include "assets/game_assets.h"
#include "ui/ui_layout.h"

typedef Rectangle Button;
namespace {
    bool _is_texture_valid(Texture2D texture) {
        return texture.id != 0;
    }

    Texture2D _first_valid_texture(const UIButtonStateTextures& textures) {
        if (_is_texture_valid(textures.normal)) return textures.normal;
        if (_is_texture_valid(textures.hover)) return textures.hover;
        if (_is_texture_valid(textures.pressed)) return textures.pressed;
        if (_is_texture_valid(textures.selected)) return textures.selected;
        return Texture2D{};
    }

    Texture2D _pick_texture(const UIButtonStateTextures& textures, UIButtonState state, bool isSelected) {
        if (isSelected && _is_texture_valid(textures.selected)) return textures.selected;
        if (state == UI_BTN_PRESSED && _is_texture_valid(textures.pressed)) return textures.pressed;
        if (state == UI_BTN_HOVER && _is_texture_valid(textures.hover)) return textures.hover;
        if (_is_texture_valid(textures.normal)) return textures.normal;
        return _first_valid_texture(textures);
    }

   
    int g_pressedButtonId = -1;
    int g_clickOwner = -1;
    bool g_interactionEnabled = true;
}

void ui_button_set_interaction_enabled(bool enabled) {
    g_interactionEnabled = enabled;
}

void ui_button_reset_active() {
    g_pressedButtonId = -1;
    g_clickOwner = -1;
}

UIButtonState ui_button_get_state(int buttonId, Button button) {
    if (!g_interactionEnabled) {
        return UI_BTN_NORMAL;
    }

    const Vector2 mouse = GetMousePosition();
    const bool hover = CheckCollisionPointRec(mouse, button);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (hover) {
            g_pressedButtonId = buttonId;
        }
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && g_pressedButtonId == buttonId) {
        g_pressedButtonId = -1;
    }

   
    if (g_pressedButtonId == buttonId && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && hover) {
        return UI_BTN_PRESSED;
    }

    if (hover) {
        return UI_BTN_HOVER;
    }

    return UI_BTN_NORMAL;
}

bool ui_button_is_clicked(int buttonId, Button button) {
    if (!g_interactionEnabled) {
        return false;
    }

    const Vector2 mouse = GetMousePosition();
    const bool hover = CheckCollisionPointRec(mouse, button);

  
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (hover) {
            g_clickOwner = buttonId;
        }
    }

    /*
        Click hợp lệ: ấn chuột khi ở trong nút (g_clickOwner == buttonId)
        VÀ thả chuột khi vẫn ở trong nút (hover == true)
        Nếu drag ra ngoài rồi thả → không tính là click
    */
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        const bool isOwner = (g_clickOwner == buttonId);
        const bool clicked = isOwner && hover;

        if (isOwner) {
            g_clickOwner = -1;
        }

        if (clicked) {
            if (g_assets.sounds.click.frameCount > 0) {
                PlaySound(g_assets.sounds.click);
            }
        }

        return clicked;
    }

    return false;
}

bool ui_button_has_any_textures(const UIButtonStateTextures& textures) {
    return _is_texture_valid(_first_valid_texture(textures));
}

void ui_button_draw(Rectangle rect, const UIButtonStyle& style, UIButtonState state) {
    Color fill = style.normal;
    if (state == UI_BTN_HOVER) fill = style.hover;
    if (state == UI_BTN_PRESSED) fill = style.pressed;

    DrawRectangleRec(rect, fill);
    DrawRectangleLinesEx(rect, 2.0f, style.border);
}

void ui_button_draw_state_textures(Rectangle rect, const UIButtonStateTextures& textures, UIButtonState state, bool isSelected) {
    Texture2D tex = _pick_texture(textures, state, isSelected);

    if (tex.id == 0) return;

    ui_draw_texture_in_rect(tex, rect);
}

void ui_button_draw_state_textures_tinted(Rectangle rect, const UIButtonStateTextures& textures, UIButtonState state, bool isSelected, Color selectedTint) {
    Texture2D tex = _pick_texture(textures, state, isSelected);

    if (tex.id == 0) return;

    Color tint = isSelected ? selectedTint : WHITE;

    ui_draw_texture_in_rect(tex, rect, tint);
}

void ui_button_draw_text(
    Rectangle rect, const char* text, Font font, float fontSize,
    UIButtonState state, Color normal, Color hover, Color pressed
) {
    if (text == nullptr) return;

    Color c = normal;
    if (state == UI_BTN_HOVER) c = hover;
    if (state == UI_BTN_PRESSED) c = pressed;

    Vector2 pos = ui_text_position_in_rect(rect, font, text, fontSize, 1.0f, 0.5f, 0.5f);

    DrawTextEx(font, text, pos, fontSize, 1.0f, c);
}
