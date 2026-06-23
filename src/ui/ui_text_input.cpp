#include "ui/ui_text_input.h"

#include <cstring>

namespace {
    constexpr double backspaceRepeatDelay = 0.45;
    constexpr double backspaceRepeatInterval = 0.06;

    bool g_backspaceHeld = false;
    double g_nextBackspaceRepeatTime = 0.0;


    int _append_input_character(char* buffer, int capacity, int length, int codepoint) {    
        if (codepoint < 32) {
            return length;
        }

        int utf8Size = 0;
        const char* utf8 = CodepointToUTF8(codepoint, &utf8Size);
        if (utf8 == nullptr || utf8Size <= 0) {
            return length;
        }

        if (length + utf8Size >= capacity) {
            return length;
        }

        std::memcpy(buffer + length, utf8, utf8Size);

        length += utf8Size;
        buffer[length] = '\0';

        return length;
    }

    void _remove_last_character(char* buffer, int length) {
        if (length <= 0 || buffer == nullptr || buffer[0] == '\0') {
            return;
        }

        int newLength = length - 1;
        while (newLength > 0 && (((unsigned char)buffer[newLength] & 0xC0) == 0x80)) {
            --newLength;
        }

        buffer[newLength] = '\0';
    }

    bool _should_delete_backspace(bool active) {
        if (!active) {
            g_backspaceHeld = false;
            g_nextBackspaceRepeatTime = 0.0;
            return false;
        }

        const double now = GetTime();

        if (IsKeyPressed(KEY_BACKSPACE)) {
            g_backspaceHeld = true;
            g_nextBackspaceRepeatTime = now + backspaceRepeatDelay;
            return true;
        }

        if (!IsKeyDown(KEY_BACKSPACE)) {
            g_backspaceHeld = false;
            g_nextBackspaceRepeatTime = 0.0;
            return false;
        }

        if (now >= g_nextBackspaceRepeatTime) {
            g_nextBackspaceRepeatTime = now + backspaceRepeatInterval;
            return true;
        }

        return false;
    }
}

bool ui_text_input_is_clicked(Rectangle rect) {
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
           CheckCollisionPointRec(GetMousePosition(), rect);
}

void ui_text_input_update(char* buffer, int capacity, bool active) {
    if (!active || buffer == nullptr || capacity <= 1) {
        return;
    }

    int length = (int)std::strlen(buffer);

    int codepoint = GetCharPressed();
    while (codepoint > 0) {
        length = _append_input_character(buffer, capacity, length, codepoint);
        codepoint = GetCharPressed();
    }

    if (_should_delete_backspace(active) && length > 0) {
        _remove_last_character(buffer, length);
    }
}

void ui_text_input_draw(
    Rectangle rect,
    const char* text,
    const char* placeholder,
    Font font,
    float fontSize,
    bool active,
    const UITextInputStyle& style
) {
    const Color fillColor = active ? style.fillActive : style.fill;
    const Color borderColor = active ? style.borderActive : style.border;

    DrawRectangleRec(rect, fillColor);
    DrawRectangleLinesEx(rect, 2.0f, borderColor);

    const bool hasText = (text != nullptr && text[0] != '\0');
    const char* displayText = hasText ? text : placeholder;
    const Color textColor = hasText ? style.text : style.placeholder;

    Vector2 textSize = MeasureTextEx(font, displayText, fontSize, 1.0f);
    Vector2 textPos = {
        rect.x + 16.0f,
        rect.y + (rect.height - textSize.y) * 0.5f
    };

    DrawTextEx(font, displayText, textPos, fontSize, 1.0f, textColor);

    if (active) {
        const char* rawValue = (text != nullptr) ? text : "";
        Vector2 valueSize = MeasureTextEx(font, rawValue, fontSize, 1.0f);
        const float caretX = textPos.x + valueSize.x + 2.0f;
        const float caretHeight = rect.height * 0.6f;
        const float caretY = rect.y + (rect.height - caretHeight) * 0.5f;
        
        if (((int)(GetTime() * 2.0)) % 2 == 0) {
            DrawRectangle(
                (int)caretX,
                (int)caretY,
                2,
                (int)caretHeight,
                style.text
            );
        }
    }
}
