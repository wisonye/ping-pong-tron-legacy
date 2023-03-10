#include "scoreboard.h"

#include <raylib.h>
#include <stdio.h>

#define BORDER_HEIGHT_PERCENT 10
#define BORDER_THICKNESS 2.0f
#define VS_FONT_SIZE 30.f
#define VS_FONT_SPACE 10.0f
#define PLAYER_FONT_SPACE 5.0f
#define PLAYER_NAME_FONT_SIZE 30.f
#define PLAYER_SCORE_FONT_SIZE 50.f
#define SPACE_BETWEEN_NAME_AND_BORDER 50.f
#define SPACE_BETWEEN_NAME_AND_SCORE 50.f

///
///
///
void draw_player_name_and_score(const char *name, usize score, bool is_player_1,
                                const Font *font, const Rectangle *container,
                                Color color) {
    //
    // Name
    //
    Vector2 name_font_size =
        MeasureTextEx(*font, name, PLAYER_NAME_FONT_SIZE, PLAYER_FONT_SPACE);
    Vector2 name_point = (Vector2){
        .x = is_player_1 ? container->x + SPACE_BETWEEN_NAME_AND_BORDER
                         : container->x + container->width -
                               SPACE_BETWEEN_NAME_AND_BORDER - name_font_size.x,
        .y = container->y + ((container->height - name_font_size.y) / 2),
    };
    DrawTextEx(*font, name, name_point, PLAYER_NAME_FONT_SIZE,
               PLAYER_FONT_SPACE, color);

    //
    // Score (double digits)
    //
    char score_str[5];
    snprintf(score_str, sizeof(score_str), score < 10 ? "0%llu" : "%llu",
             score);

    Vector2 score_font_size = MeasureTextEx(
        *font, score_str, PLAYER_SCORE_FONT_SIZE, PLAYER_FONT_SPACE);
    Vector2 score_font_point = (Vector2){
        .x = is_player_1 ? name_point.x + name_font_size.x +
                               SPACE_BETWEEN_NAME_AND_SCORE
                         : name_point.x - SPACE_BETWEEN_NAME_AND_SCORE -
                               score_font_size.x,
        .y = container->y + ((container->height - score_font_size.y) / 2),
    };
    DrawTextEx(*font, score_str, score_font_point, PLAYER_SCORE_FONT_SIZE,
               PLAYER_FONT_SPACE, color);
}

///
///
///
Rectangle SB_redraw(const Scoreboard *sb, const float ui_padding,
                    Color border_color) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    //
    // Outside border
    //
    Rectangle rect = (Rectangle){
        .x = ui_padding,
        .y = ui_padding,
        .width = screen_width - 2 * ui_padding,
        .height = (float)screen_height * ((float)BORDER_HEIGHT_PERCENT / 100),
    };

    // TraceLog(LOG_DEBUG, ">>> [ SB_redraw ] - rect: %f, %f, %f, %f", rect.x,
    // rect.y, rect.width, rect.height);

    DrawRectangleLinesEx(rect, BORDER_THICKNESS, border_color);

    //
    // `VS`
    //
    Font font = GetFontDefault();
    Vector2 vs_font_size =
        MeasureTextEx(font, "VS", VS_FONT_SIZE, VS_FONT_SPACE);
    // TraceLog(LOG_DEBUG, ">>> [ SB_redraw ] - vs_font_size: %f, %f",
    // vs_font_size.x, vs_font_size.y);

    float vs_font_draw_x = rect.x + ((rect.width - vs_font_size.x) / 2);
    float vs_font_draw_y = rect.y + ((rect.height - vs_font_size.y) / 2);
    Vector2 vs_font_point = (Vector2){
        .x = vs_font_draw_x,
        .y = vs_font_draw_y,
    };
    DrawTextEx(font, "VS", vs_font_point, VS_FONT_SIZE, VS_FONT_SPACE,
               border_color);
    // TraceLog(LOG_DEBUG, ">>> [ SB_redraw ] - vs_font_point: %f, %f",
    // vs_font_point.x, vs_font_point.y);

    //
    // Player
    //
    draw_player_name_and_score(sb->player_1_name, sb->player_1_score, true,
                               &font, &rect, border_color);
    draw_player_name_and_score(sb->player_2_name, sb->player_2_score, false,
                               &font, &rect, border_color);

    return rect;
}

///
///
///
void SB_update_player_1_score(Scoreboard *sb, usize score);

///
///
///
void SB_update_player_2_score(Scoreboard *sb, usize score);
