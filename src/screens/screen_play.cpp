#include "screens/screen_play.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "ai/ai.h"
#include "app/game_app.h"
#include "assets/game_assets.h"
#include "config/config.h"
#include "game/game.h"
#include "raylib.h"
#include "render/theme.h"
#include "screens/screens.h"
#include "ui/ui.h"
namespace {
    int _min_int(int a, int b) {
        return (a < b) ? a : b;
    }
    int _max_int(int a, int b) {
        return (a > b) ? a : b;
    }
    float _min_float(float a, float b) {
        return (a < b) ? a : b;
    }
    float _max_float(float a, float b) {
        return (a > b) ? a : b;
    }
    float _clamp_float(float value, float minValue, float maxValue) {
        return _max_float(minValue, _min_float(value, maxValue));
    }
    
    constexpr int   BTN_CONFIRM_ID     = 101;
    constexpr int   BTN_HINT_ID        = 102;
    constexpr int   BTN_PAUSE_ID       = 103;
    constexpr int   BTN_SOUND_ID       = 104;
    constexpr int   BTN_MUSIC_ID       = 105;
    
    constexpr int   MaxAnimatedClouds = 32;
    
    constexpr float AiBaseThinkDelay  = 1.1f;
    constexpr float AiStepThinkDelay  = 0.25f;

    // Thời gian animation của đám mây khi bốc.
    constexpr float FlightDuration    = 0.82f;
    
    const Rectangle SCORE_CARD_P1 = {340.0f, 15.0f, 280.0f, 80.0f};
    const Rectangle SCORE_CARD_P2 = {660.0f, 15.0f, 280.0f, 80.0f};
    const Rectangle HEADER_SUMMARY = {0.0f, 110.0f, 1280.0f, 20.0f};

    // Nút và khung cố định trong màn chơi.
    const Rectangle BTN_CONFIRM = {490.0f, 615.0f, 300.0f, 64.0f};
    const Rectangle BTN_HINT = {1080.0f, 622.0f, 172.0f, 64.0f};
    const Rectangle BTN_PAUSE = {1184.0f, 20.0f, 56.0f, 56.0f};
    // Sound và Music nằm bên trái Pause, cách nhau 8px.
    const Rectangle BTN_SOUND = {1120.0f, 20.0f, 56.0f, 56.0f};
    const Rectangle BTN_MUSIC = {1056.0f, 20.0f, 56.0f, 56.0f};

    const Rectangle BOARD_RECT = {104.0f, 200.0f, 1072.0f, 376.0f};
     
    const Color CLOUD_SHADOW_COLOR    = ColorAlpha(DARKBLUE, 0.29f);
    const Color CLOUD_FILL_NORMAL     = ColorAlpha(RAYWHITE, 0.97f);
    const Color CLOUD_OUTLINE_NORMAL  = DARKBLUE;
    const Color CLOUD_ACCENT_NORMAL   = SKYBLUE;
    const Color CLOUD_FILL_DISABLED   = LIGHTGRAY;
    const Color CLOUD_OUTLINE_DISABLED= GRAY;
    const Color CLOUD_ACCENT_DISABLED = ColorAlpha(LIGHTGRAY, 0.80f);
    const Color CLOUD_FILL_SELECTED   = ColorAlpha(GOLD, 0.95f);
    const Color CLOUD_OUTLINE_SELECTED= ORANGE;
    const Color CLOUD_ACCENT_SELECTED = YELLOW;
    const Color CLOUD_FILL_HOVER      = WHITE;
    const Color CLOUD_OUTLINE_HOVER   = BLUE;
    const Color CLOUD_ACCENT_HOVER    = ColorAlpha(SKYBLUE, 0.90f);
    const Color CLOUD_FILL_PRESSED    = ColorAlpha(RAYWHITE, 0.87f);
    const Color CLOUD_OUTLINE_PRESSED = DARKBLUE;
    const Color CLOUD_ACCENT_PRESSED  = SKYBLUE;
    const Color CLOUD_TEXT_NORMAL     = DARKBLUE;
    const Color CLOUD_TEXT_DISABLED   = DARKGRAY;
    
    const Color SCORE_CARD_FILL_ACTIVE = ColorAlpha(BLACK, 0.87f);
    const Color SCORE_CARD_FILL_IDLE   = ColorAlpha(BLACK, 0.77f);
   
    const Color BOARD_FILL_COLOR   = ColorAlpha(DARKBLUE, 0.65f);
    const Color BOARD_BORDER_COLOR = ColorAlpha(SKYBLUE,  0.45f);

    struct CloudFlightState {
        bool active = false;
        Move move{};
        int actorIndex = 0;
        double startTime = 0.0;
        Vector2 startPositions[MaxAnimatedClouds]{};
        Vector2 size{};
    };

    bool g_hasSession = false;
    bool g_gameInitialized = false;

    MatchConfig g_matchConfig{};
    GameSettings g_roundSettings{};
    GameState g_game{};

    int g_seriesScore[2] = {0, 0};
    int g_roundPileCount = 3;

    Move g_selectedMove{-1, 0};
    Move g_aiMove{-1, 0};

    bool g_aiThinking = false;
    double g_aiThinkUntil = 0.0;
    
    CloudFlightState g_cloudFlight{};

    // Kiểm tra xem round có giới hạn lượt bốc hay không.
    bool _uses_take_limit() {
        return g_roundSettings.maxTakePerMove > 0;
    }
    
    // * label -------------------------------------
    const char* _mode_label(GameMode mode) {
        switch (mode) {
            case GAME_MODE_PVP:   return u8"Đối kháng";
            case GAME_MODE_PVAI:  return u8"Người chơi và AI";
            default: return u8"UNKNƠ";
        }
    }
    
    const char* _rule_label(GameRule rule) {
        return (rule == GAME_RULE_LAST_TAKE_WIN)
            ? u8"Bốc cuối thắng"
            : u8"Bốc cuối thua";
    }

    const char* _actor_name_internal(int actorIndex) {
        if (actorIndex < 0 || actorIndex > 1) {
            return "";
        }
        const char* name = g_matchConfig.players[actorIndex].name;
        if (name[0] != '\0') {
            return name;
        }
        if (g_matchConfig.players[actorIndex].type == PLAYER_TYPE_AI) {
            return u8"AI";
        }
        return (actorIndex == 0) ? u8"Người chơi 1" : u8"Người chơi 2";
    }
    // tới lượt thì dùng màu khác.
    Color _actor_color(int actorIndex, bool active) {
        if (actorIndex == 0) {
            return active ? THEME_ACCENT_COLOR : THEME_TEXT_COLOR;
        }
        return active ? THEME_ACCENT_COLOR : THEME_TEXT_COLOR;
    }
   
    // tinhs chieeuf cao cao mỗi hàng trong board.
    float _row_height() {
        return BOARD_RECT.height / (float)_max_int(1, g_game.piles.size);
    }
    // Lấy số mây nhiều nhất trong một đống để canh kích thước.
    float _max_visible_clouds() {
        int maxClouds = 1;
        for (int pileIndex = 0; pileIndex < g_game.piles.size; ++pileIndex) {
            maxClouds = _max_int(maxClouds, get(g_game.piles, pileIndex));
        }
        return (float)maxClouds;
    }

    // Tính kích thước mây từ board và số đống hiện có.
    Vector2 _cloud_size() {
        const Rectangle board = BOARD_RECT;
        const float labelWidth = 136.0f;
        const float leftPadding = 22.0f;
        const float maxClouds = _max_visible_clouds();
        const float gap = 10.0f;
        const float widthByBoard = (board.width - labelWidth - leftPadding - gap * (maxClouds - 1.0f)) / _max_float(1.0f, maxClouds);
        const float widthByRow = (_row_height() * 0.72f) / 0.58f;
        const float maxWidth = (g_game.piles.size <= 5) ? 82.0f : 68.0f;
        const float minWidth = (g_game.piles.size <= 5) ? 42.0f : 28.0f;
        const float width = _min_float(widthByBoard, widthByRow);
        const float clampedWidth = _clamp_float(width, minWidth, maxWidth);
        return Vector2{clampedWidth, clampedWidth * 0.58f};
    }

    // Tính rect của từng đám mây trong board.
    Rectangle _cloud_rect(int pileIndex, int cloudIndex) {
        const Rectangle board = BOARD_RECT;
        const Vector2 cloudSize = _cloud_size();
        const float labelWidth = 136.0f;
        const float leftPadding = 22.0f;
        const float gap = 10.0f;
        const float rowTop = board.y + _row_height() * (float)pileIndex;
        const float startX = board.x + labelWidth + leftPadding;
        const float y = rowTop + (_row_height() - cloudSize.y) * 0.5f;
        return Rectangle{
            startX + cloudIndex * (cloudSize.x + gap),
            y,
            cloudSize.x,
            cloudSize.y
        };
    }

    // ID "nút" riêng cho từng mây để xử lý click.
    int _cloud_button_id(int pileIndex, int cloudIndex) {
        return 10000 + pileIndex * 100 + cloudIndex;
    }
    
    bool _is_ai_turn() {
        if (!g_hasSession || !g_gameInitialized) {
            return false;
        }
        return g_game.matchConfig.players[g_game.currentTurn].type == PLAYER_TYPE_AI;
    }
    
    bool _is_human_turn() {
        return g_hasSession && g_gameInitialized && !_is_ai_turn();
    }

    
    float _ai_think_delay() {
        const AIDifficulty difficulty = g_game.matchConfig.players[g_game.currentTurn].difficulty;
        return AiBaseThinkDelay + AiStepThinkDelay * (float)difficulty;
    }
    // Tính người thắng theo luật hiện tại.
    int _winner_index() {
        int winner = g_game.currentTurn;
        if (g_roundSettings.gameRule == GAME_RULE_LAST_TAKE_LOSE) {
            winner = 1 - winner;
        }
        return winner;
    }

    // Bỏ chọn đám mây hiện tại.
    void _clear_selection() {
        g_selectedMove = Move{-1, 0};
    }

    
    void _begin_turn() {
        _clear_selection();
        g_aiThinking = false;
        g_aiMove = Move{-1, 0};
        if (_is_ai_turn()) {
            g_aiThinking = true;
            g_aiMove = choose_ai_move(g_game);
            g_aiThinkUntil = GetTime() + _ai_think_delay();
        }
    }

    // Khởi tạo lại round hiện tại.
    void _initialize_round(bool resetScore) {
        if (g_gameInitialized) {
            free_game(g_game);
            g_gameInitialized = false;
        }
        // Moi round đều random nguoi di truoc
        const int startingTurn = GetRandomValue(0, 1);
        init_game(g_game, g_roundPileCount, g_matchConfig, g_roundSettings, startingTurn);
        g_gameInitialized = true;
        g_cloudFlight = {};
        g_aiThinking = false;
        g_aiThinkUntil = 0.0;
        g_aiMove = Move{-1, 0};
        _clear_selection();
        if (resetScore) {
            g_seriesScore[0] = 0;
            g_seriesScore[1] = 0;
        }
        _begin_turn();
    }

    // Vẽ mây fallback bằng shape khi không có texture.
    void _draw_cloud_shape(Rectangle rect, Color fillColor, Color outlineColor, Color accentColor) {
        const Rectangle shadowRect = {
            rect.x + 3.0f,
            rect.y + 4.0f,
            rect.width,
            rect.height
        };
        DrawEllipse(
            (int)(shadowRect.x + shadowRect.width * 0.46f),
            (int)(shadowRect.y + shadowRect.height * 0.70f),
            shadowRect.width * 0.34f,
            shadowRect.height * 0.20f,
            CLOUD_SHADOW_COLOR
        );
        DrawRectangleRounded(
            Rectangle{rect.x + rect.width * 0.16f, rect.y + rect.height * 0.42f, rect.width * 0.68f, rect.height * 0.34f},
            0.55f,
            8,
            fillColor
        );
        DrawCircleV(Vector2{rect.x + rect.width * 0.30f, rect.y + rect.height * 0.50f}, rect.height * 0.22f, fillColor);
        DrawCircleV(Vector2{rect.x + rect.width * 0.48f, rect.y + rect.height * 0.32f}, rect.height * 0.30f, fillColor);
        DrawCircleV(Vector2{rect.x + rect.width * 0.68f, rect.y + rect.height * 0.48f}, rect.height * 0.24f, fillColor);
        DrawCircleLinesV(Vector2{rect.x + rect.width * 0.30f, rect.y + rect.height * 0.50f}, rect.height * 0.22f, outlineColor);
        DrawCircleLinesV(Vector2{rect.x + rect.width * 0.48f, rect.y + rect.height * 0.32f}, rect.height * 0.30f, outlineColor);
        DrawCircleLinesV(Vector2{rect.x + rect.width * 0.68f, rect.y + rect.height * 0.48f}, rect.height * 0.24f, outlineColor);
        DrawRectangleRoundedLinesEx(
            Rectangle{rect.x + rect.width * 0.16f, rect.y + rect.height * 0.42f, rect.width * 0.68f, rect.height * 0.34f},
            0.55f,
            8,
            2.0f,
            outlineColor
        );
        DrawCircleV(Vector2{rect.x + rect.width * 0.40f, rect.y + rect.height * 0.30f}, rect.height * 0.09f, accentColor);
    }

    // Vẽ một đám mây tương tác.
    void _draw_cloud_button(Rectangle rect, int takeCount, UIButtonState state, bool isSelected, bool isSelectable) {
        if (ui_button_has_any_textures(g_assets.buttons.cloud)) {
            ui_button_draw_state_textures(rect, g_assets.buttons.cloud, isSelectable ? state : UI_BTN_NORMAL, isSelected);
            if (!isSelectable) {
                DrawRectangleRounded(rect, 0.30f, 8, Fade(BLACK, 0.22f));
            }
        } else {
            Color fillColor = CLOUD_FILL_NORMAL;
            Color outlineColor = CLOUD_OUTLINE_NORMAL;
            Color accentColor = CLOUD_ACCENT_NORMAL;
            if (!isSelectable) {
                fillColor = CLOUD_FILL_DISABLED;
                outlineColor = CLOUD_OUTLINE_DISABLED;
                accentColor = CLOUD_ACCENT_DISABLED;
            } else if (isSelected) {
                fillColor = CLOUD_FILL_SELECTED;
                outlineColor = CLOUD_OUTLINE_SELECTED;
                accentColor = CLOUD_ACCENT_SELECTED;
            } else if (state == UI_BTN_HOVER) {
                fillColor = CLOUD_FILL_HOVER;
                outlineColor = CLOUD_OUTLINE_HOVER;
                accentColor = CLOUD_ACCENT_HOVER;
            } else if (state == UI_BTN_PRESSED) {
                fillColor = CLOUD_FILL_PRESSED;
                outlineColor = CLOUD_OUTLINE_PRESSED;
                accentColor = CLOUD_ACCENT_PRESSED;
            }
            _draw_cloud_shape(rect, fillColor, outlineColor, accentColor);
        }
        ui_draw_text_in_rect_with_outline(
            g_assets.fonts.common,
            TextFormat("%d", takeCount),
            rect,
            rect.height * 0.54f,
            1.0f,
            0.50f,
            0.50f,
            1.0f,
            isSelectable ? CLOUD_TEXT_NORMAL : CLOUD_TEXT_DISABLED,
            WHITE
        );
    }

    // * Bắt đầu animation bay 
    void _start_flight(const Move& move, int actorIndex) {
        g_cloudFlight = {};
        g_cloudFlight.active = true;
        g_cloudFlight.move = move;
        g_cloudFlight.actorIndex = actorIndex;
        g_cloudFlight.startTime = GetTime();
        g_cloudFlight.size = _cloud_size();
        const int animatedCount = _min_int(move.stoneCount, MaxAnimatedClouds);
        for (int i = 0; i < animatedCount; ++i) {
            const Rectangle rect = _cloud_rect(move.pileIndex, i);
            g_cloudFlight.startPositions[i] = Vector2{rect.x, rect.y};
        }
        _clear_selection();
        g_aiThinking = false;
    }
    // * Kết thúc animation và áp move vào game.
    void _finish_flight(GameAppState& app) {
        const Move move = g_cloudFlight.move;
        g_cloudFlight.active = false;
        if (!apply_move(g_game, move)) {
            _begin_turn();
            return;
        }
        if (is_game_over(g_game)) {
            const int winnerIndex = _winner_index();
            ++g_seriesScore[winnerIndex];
            char resultText[96];
            std::snprintf(resultText, sizeof(resultText), u8"%s Thắng ván này!", _actor_name_internal(winnerIndex));
            game_app_show_result(app, resultText);
            if (g_assets.sounds.end.frameCount > 0) {
                PlaySound(g_assets.sounds.end);
            }
            return;
        }
        next_turn(g_game);
        _begin_turn();
    }

    // Score card chia 2 vùng: trên là tên, dưới là điểm thắng.
    void _draw_score_card(Rectangle rect, int actorIndex, bool active) {
        const Color borderColor = _actor_color(actorIndex, active);
        const Color fillColor   = active ? SCORE_CARD_FILL_ACTIVE : SCORE_CARD_FILL_IDLE;
        DrawRectangleRounded(rect, 0.16f, 10, fillColor);
        DrawRectangleRoundedLinesEx(rect, 0.16f, 10, 3.5f, borderColor);
        // Vùng trên hiển thị tên người chơi.
        const Rectangle nameRect  = {rect.x, rect.y,              rect.width, rect.height * 0.56f};
        // Vùng dưới hiển thị số ván thắng.
        const Rectangle scoreRect = {rect.x, rect.y + rect.height * 0.56f, rect.width, rect.height * 0.44f};
        ui_draw_text_in_rect_with_outline(
            g_assets.fonts.common,
            _actor_name_internal(actorIndex),
            nameRect,
            26.0f, 1.0f, 0.5f, 0.5f, 1.0f,
            borderColor, BLACK
        );
        ui_draw_text_in_rect(
            g_assets.fonts.common,
            TextFormat(u8"Thắng: %d", g_seriesScore[actorIndex]),
            scoreRect,
            20.0f, 1.0f, 0.5f, 0.5f,
            THEME_TEXT_COLOR
        );
    }
    // Thanh đầu màn hình gồm 2 score card và dòng mô tả luật.
    void _draw_header() {
        _draw_score_card(SCORE_CARD_P1, 0, g_game.currentTurn == 0);
        _draw_score_card(SCORE_CARD_P2, 1, g_game.currentTurn == 1);

        char summary[96];
        if (_uses_take_limit()) {
            std::snprintf(summary, sizeof(summary), u8"%s         Tối đa %d/lượtt", _rule_label(g_roundSettings.gameRule), g_roundSettings.maxTakePerMove);
        } else {
            std::snprintf(summary, sizeof(summary), u8"%s         Không giới hạn", _rule_label(g_roundSettings.gameRule));
        }
        ui_draw_text_in_rect_with_outline(
            g_assets.fonts.common, summary,
            HEADER_SUMMARY,
            22.0f, 3.0f, 0.5f, 0.5f, 2.0f,
            THEME_ACCENT_COLOR, BLACK
        );
    }
    
    // Vẽ board, nhãn đống và toàn bộ mây trong mỗi đống.
    void _draw_pile_labels_and_clouds() {
        DrawRectangleRounded(BOARD_RECT, 0.08f, 8, BOARD_FILL_COLOR);
        DrawRectangleRoundedLinesEx(BOARD_RECT, 0.08f, 8, 2.0f, BOARD_BORDER_COLOR);

        for (int pileIndex = 0; pileIndex < g_game.piles.size; ++pileIndex) {
            int visibleCloudCount = get(g_game.piles, pileIndex);
            if (g_cloudFlight.active && g_cloudFlight.move.pileIndex == pileIndex) {
                visibleCloudCount -= g_cloudFlight.move.stoneCount;
            }
            const float rowTop = BOARD_RECT.y + _row_height() * (float)pileIndex;
            const Rectangle labelRect = {BOARD_RECT.x + 16.0f, rowTop + 8.0f, 118.0f, _row_height() - 16.0f};

            // Nhãn đống dùng màu label chung.
            ui_draw_text_in_rect(
                g_assets.fonts.common,
                TextFormat(u8"Cụm %d", pileIndex + 1),
                labelRect,
                22.0f,
                1.0f,
                0.0f,
                0.5f,
                UI_COLOR_LABEL
            );
            // Tìm đám mây nào trong hàng đang được hover/pressed để lan trạng thái đó
            // sang tất cả đám mây phía trước (vì bốc là bốc từ đầu tới chỗ chọn).
            const bool rowSelectable =
                _is_human_turn() &&
                !g_cloudFlight.active &&
                !g_aiThinking;
            int hoveredUpTo = -1; // cloudIndex cao nhất đang bị hover/pressed trong hàng này
            if (rowSelectable) {
                for (int cloudIndex = 0; cloudIndex < visibleCloudCount; ++cloudIndex) {
                    const Rectangle cloudRect = _cloud_rect(pileIndex, cloudIndex);
                    const Move candidateMove = {pileIndex, cloudIndex + 1};
                    if (!is_valid_move(g_game, candidateMove)) continue;
                    const UIButtonState s = ui_button_get_state(_cloud_button_id(pileIndex, cloudIndex), cloudRect);
                    if (s == UI_BTN_HOVER || s == UI_BTN_PRESSED) {
                        hoveredUpTo = cloudIndex;
                    }
                }
            }

            for (int cloudIndex = 0; cloudIndex < visibleCloudCount; ++cloudIndex) {
                const Rectangle cloudRect = _cloud_rect(pileIndex, cloudIndex);
                const Move candidateMove = {pileIndex, cloudIndex + 1};
                const bool isSelectable = rowSelectable && is_valid_move(g_game, candidateMove);

                UIButtonState state = UI_BTN_NORMAL;
                if (isSelectable) {
                    // Nếu đám mây này nằm trong vùng hover (từ đầu đến hoveredUpTo),
                    // lan state HOVER để phản ánh "sẽ bốc từ đây đến đó".
                    if (cloudIndex < hoveredUpTo) {
                        state = UI_BTN_HOVER;
                    } else {
                        state = ui_button_get_state(_cloud_button_id(pileIndex, cloudIndex), cloudRect);
                    }
                }

                const bool isSelected =
                    (g_selectedMove.pileIndex == pileIndex) &&
                    (cloudIndex < g_selectedMove.stoneCount);
                _draw_cloud_button(cloudRect, cloudIndex + 1, state, isSelected, isSelectable);
            }
        }
    }
    // Vẽ các đám mây đang bay sau khi vừa bốc.
    void _draw_flying_clouds() {
        if (!g_cloudFlight.active) {
            return;
        }
        const int count = _min_int(g_cloudFlight.move.stoneCount, MaxAnimatedClouds);
        const float elapsed = (float)(GetTime() - g_cloudFlight.startTime);
        const float t = _clamp_float(elapsed / FlightDuration, 0.0f, 1.0f);
        const float eased = 1.0f - std::pow(1.0f - t, 3.0f);
        const float endX = (g_cloudFlight.actorIndex == 0)
            ? (-g_cloudFlight.size.x - 80.0f)
            : ((float)AppConfig::WINDOW_WIDTH + 80.0f); // Bay tới mép màn hình cố định.
        for (int i = 0; i < count; ++i) {
            const Vector2 start = g_cloudFlight.startPositions[i];
            const float x = start.x + (endX - start.x) * eased;
            const float y = start.y - 56.0f * std::sin(eased * 3.1415926f) - 26.0f * eased;
            const Rectangle rect = {x, y, g_cloudFlight.size.x, g_cloudFlight.size.y};
            const unsigned char alpha = (unsigned char)(255.0f * (1.0f - eased));
            const Texture2D selectedTexture = g_assets.buttons.cloud.selected;
            // Alpha giảm dần để mây tan dần trong lúc bay.
            const float fAlpha = (float)alpha / 255.0f;
            if (selectedTexture.id != 0) {
                const Rectangle src = {0.0f, 0.0f, (float)selectedTexture.width, (float)selectedTexture.height};
                DrawTexturePro(
                    selectedTexture,
                    src,
                    rect,
                    Vector2{0.0f, 0.0f},
                    0.0f,
                    ColorAlpha(WHITE, fAlpha)
                );
            } else {
                _draw_cloud_shape(
                    rect,
                    ColorAlpha(GOLD,   fAlpha),
                    ColorAlpha(ORANGE, fAlpha),
                    ColorAlpha(YELLOW, fAlpha)
                );
            }
        }
    }

    // Nút xác nhận hiện ra khi người chơi đã chọn xong.
    void _draw_selection_summary() {
        if (g_selectedMove.pileIndex < 0 || g_cloudFlight.active || g_aiThinking || !_is_human_turn()) {
            return;
        }
        
        const Color selectionTextColor    = THEME_ACCENT_COLOR;
        // ui_draw_text_in_rect_with_outline(
        //     g_assets.fonts.common,
        //     TextFormat(
        //         u8"Đã chọn",
        //         g_selectedMove.pileIndex + 1,
        //         g_selectedMove.stoneCount
        //     ),
        //     Rectangle{0.0f, 565.0f, (float)AppConfig::WINDOW_WIDTH, 24.0f},
        //     24.0f, 2.0f, 0.5f, 0.5f, 2.0f,
        //     selectionTextColor, selectionOutlineColor
        // );
        screen_draw_button(BTN_CONFIRM_ID, BTN_CONFIRM, u8"ĐỒNG Ý", 30.0f);
    }

    
    void _draw_turn_banner() {
        const char* text = u8"";

        Color turnTextColor    = THEME_TEXT_COLOR;
        const Color turnOutline = BLACK;

        if (g_aiThinking) {
            text         = u8"AI đang suy nghĩ...";
            turnTextColor = THEME_ACCENT_COLOR;
        } else if (g_gameInitialized && g_hasSession) {
            static char turnText[64];
            std::snprintf(turnText, sizeof(turnText), u8"Lượt của %s", _actor_name_internal(g_game.currentTurn));
            text = turnText;
        }

        ui_draw_text_in_rect_with_outline(
            g_assets.fonts.common,
            text,
            Rectangle{0.0f, 155.0f, 1280.0f, 24.0f},
            49.0f, 2.0f, 0.5f, 0.5f, 2.0f,
            turnTextColor, turnOutline
        );
    }

    
    void _draw_footer_hint() {
        const char* hintText = _is_human_turn()
            ? u8"Chọn một đám mây để bốc ngay từ bên trái đến vị trí đó, rồi nhấn Enter hoặc nút đồng ý"
            : u8"Nhấn ESC để mở tạm dừng";
            
       
        const Color hintColor   = THEME_ACCENT_COLOR;
        const Color hintOutline = BLACK;
        ui_draw_text_in_rect_with_outline(
            g_assets.fonts.common,
            hintText,
            Rectangle{0.0f, 690.0f, (float)AppConfig::WINDOW_WIDTH, 20.0f},
            26.0f, 2.0f, 0.5f, 0.5f, 2.0f,
            hintColor, hintOutline
        );
    }

    void _draw_pause_button() {
        const UIButtonState state = ui_button_get_state(BTN_PAUSE_ID, BTN_PAUSE);
        if (ui_button_has_any_textures(g_assets.buttons.pause)) {
            ui_button_draw_state_textures(BTN_PAUSE, g_assets.buttons.pause, state, false);
            return;
        }
        screen_draw_button(BTN_PAUSE_ID, BTN_PAUSE, "II", 22.0f);
    }

    // Vẽ nút bật/tắt sound — dùng texture sound_on/sound_off tùy trạng thái.
    void _draw_sound_button(const GameAppState& app) {
        const bool muted = app.settings.soundMuted;
        const UIButtonStateTextures& tex = muted ? g_assets.buttons.sound_off : g_assets.buttons.sound_on;
        const UIButtonState state = ui_button_get_state(BTN_SOUND_ID, BTN_SOUND);
        if (ui_button_has_any_textures(tex)) {
            ui_button_draw_state_textures(BTN_SOUND, tex, state, false);
            return;
        }
        // Fallback: chữ S (sound) với màu tối khi muted.
        screen_draw_button(BTN_SOUND_ID, BTN_SOUND, muted ? "Sx" : "S", 22.0f);
    }

    // Vẽ nút bật/tắt music — dùng texture music_on/music_off tùy trạng thái.
    void _draw_music_button(const GameAppState& app) {
        const bool muted = app.settings.musicMuted;
        const UIButtonStateTextures& tex = muted ? g_assets.buttons.music_off : g_assets.buttons.music_on;
        const UIButtonState state = ui_button_get_state(BTN_MUSIC_ID, BTN_MUSIC);
        if (ui_button_has_any_textures(tex)) {
            ui_button_draw_state_textures(BTN_MUSIC, tex, state, false);
            return;
        }
        // Fallback: chữ M (music) với màu tối khi muted.
        screen_draw_button(BTN_MUSIC_ID, BTN_MUSIC, muted ? "Mx" : "M", 22.0f);
    }

    void _draw_hint_button(const GameAppState& app) {
        if (!app.settings.hintsEnabled) return;
        if (!g_gameInitialized || !g_hasSession) return;
        if (g_cloudFlight.active) return;

        const bool enabled = _is_human_turn() && !g_aiThinking;
        const Rectangle rect = BTN_HINT;

        if (enabled) {
            screen_draw_button(BTN_HINT_ID, rect, u8"GỢI Ý", 26.0f);
        } else {
            screen_draw_disabled_button(BTN_HINT_ID, rect, u8"GỢI Ý", 26.0f);
        }
    }

    // Xử lý click từng đám mây để chọn số lượng muốn bốc.
    void _handle_human_cloud_selection() {
        for (int pileIndex = 0; pileIndex < g_game.piles.size; ++pileIndex) {
            const int stonesInPile = get(g_game.piles, pileIndex);
            for (int cloudIndex = 0; cloudIndex < stonesInPile; ++cloudIndex) {
                const Move candidateMove = {pileIndex, cloudIndex + 1};
                if (!is_valid_move(g_game, candidateMove)) {
                    continue;
                }

                const Rectangle cloudRect = _cloud_rect(pileIndex, cloudIndex);
                if (ui_button_is_clicked(_cloud_button_id(pileIndex, cloudIndex), cloudRect)) {
                    g_selectedMove = candidateMove;
                    return;
                }
            }
        }
    }

    // Xác nhận nước đi bằng Enter hoặc nút Đồng ý.
    void _try_confirm_human_move() {
        if (g_selectedMove.pileIndex < 0 || !is_valid_move(g_game, g_selectedMove)) {
            return;
        }

        if (IsKeyPressed(KEY_ENTER) || ui_button_is_clicked(BTN_CONFIRM_ID, BTN_CONFIRM)) {
            _start_flight(g_selectedMove, g_game.currentTurn);
        }
    }
}









// * ---------------------------------------------------------------------







// Mở một ván mới với cấu hình hiện tại.
void screen_play_start_new_match(const MatchConfig& matchConfig, const GameSettings& settings, int pileCount) {
    if (g_gameInitialized) {
        free_game(g_game);
        g_gameInitialized = false;
    }

    g_matchConfig = matchConfig;
    g_roundSettings = settings;
    g_hasSession = true;
    g_cloudFlight = {};
    g_aiThinking = false;
    g_aiThinkUntil = 0.0;
    g_aiMove = Move{-1, 0};
    g_roundPileCount = _max_int(1, pileCount);
    _clear_selection();
    _initialize_round(true);
}


void screen_play_continue_match() {
    if (!g_hasSession) {
        return;
    }

    _initialize_round(false);
}


void screen_play_shutdown() {
    if (g_gameInitialized) {
        free_game(g_game);
        g_gameInitialized = false;
    }

    g_hasSession = false;
    g_matchConfig = {};
    g_roundSettings = {};
    g_seriesScore[0] = 0;
    g_seriesScore[1] = 0;
    g_roundPileCount = 3;
    g_aiThinking = false;
    g_aiThinkUntil = 0.0;
    g_aiMove = Move{-1, 0};
    g_cloudFlight = {};
    _clear_selection();
}

// Trả tên người chơi để các màn khác dùng lại.
const char* screen_play_get_actor_name(int actorIndex) {
    return _actor_name_internal(actorIndex);
}

// Trả điểm của người chơi.
int screen_play_get_score(int actorIndex) {
    if (actorIndex < 0 || actorIndex > 1) {
        return 0;
    }

    return g_seriesScore[actorIndex];
}




void screen_play_update(GameAppState& app) {

    if (!g_hasSession) {
        app.currentScreen = APP_SCREEN_MAIN_MENU;
        return;
    }

    if (!g_gameInitialized) {
        app.currentScreen = APP_SCREEN_MAIN_MENU;
        return;
    }

    if ((IsKeyPressed(KEY_ESCAPE) || ui_button_is_clicked(BTN_PAUSE_ID, BTN_PAUSE)) && !g_cloudFlight.active) {
        app.currentOverlay = APP_OVERLAY_PAUSE;
        return;
    }

    // Toggle sound.
    if (ui_button_is_clicked(BTN_SOUND_ID, BTN_SOUND)) {
        app.settings.soundMuted = !app.settings.soundMuted;
        game_app_apply_audio_settings(app);
    }

    // Toggle music.
    if (ui_button_is_clicked(BTN_MUSIC_ID, BTN_MUSIC)) {
        app.settings.musicMuted = !app.settings.musicMuted;
        game_app_apply_audio_settings(app);
    }

    if (g_cloudFlight.active) {
        if ((GetTime() - g_cloudFlight.startTime) >= FlightDuration) {
            _finish_flight(app);
        }
        return;
    }

    if (g_aiThinking) {
        if (GetTime() >= g_aiThinkUntil && is_valid_move(g_game, g_aiMove)) {
            _start_flight(g_aiMove, g_game.currentTurn);
        }
        return;
    }

    if (!_is_human_turn()) {
        _begin_turn();
        return;
    }

    _handle_human_cloud_selection();
    _try_confirm_human_move();

    if (app.settings.hintsEnabled && _is_human_turn() && !g_cloudFlight.active && !g_aiThinking) {
        if (ui_button_is_clicked(BTN_HINT_ID, BTN_HINT)) {
            const Move hint = choose_hint_move(g_game);
            if (is_valid_move(g_game, hint)) {
                g_selectedMove = hint;
            }
        }
    }
}


void screen_play_draw(const GameAppState& app) {
    
    ClearBackground(THEME_BG_COLOR);
    screen_draw_background(g_assets.images.bg_play, THEME_BG_COLOR);

    if (!g_gameInitialized) {
        return;
    }

    _draw_header();
    _draw_pause_button();
    _draw_sound_button(app);
    _draw_music_button(app);
    _draw_turn_banner();
    _draw_pile_labels_and_clouds();
    _draw_flying_clouds();
    _draw_selection_summary();
    _draw_hint_button(app);
    _draw_footer_hint();
}
