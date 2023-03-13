#include "scoreboard.h"

#include <raylib.h>
#include <stdio.h>

#include "config.h"

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
        MeasureTextEx(*font, name, SCOREBOARD_UI_PLAYER_NAME_FONT_SIZE,
                      SCOREBOARD_UI_PLAYER_FONT_SPACE);
    Vector2 name_point = (Vector2){
        .x = is_player_1
                 ? container->x + SCOREBOARD_UI_SPACE_BETWEEN_NAME_AND_BORDER
                 : container->x + container->width -
                       SCOREBOARD_UI_SPACE_BETWEEN_NAME_AND_BORDER -
                       name_font_size.x,
        .y = container->y + ((container->height - name_font_size.y) / 2),
    };
    DrawTextEx(*font, name, name_point, SCOREBOARD_UI_PLAYER_NAME_FONT_SIZE,
               SCOREBOARD_UI_PLAYER_FONT_SPACE, color);

    //
    // Score (double digits)
    //
    char score_str[5];
    snprintf(score_str, sizeof(score_str), score < 10 ? "0%llu" : "%llu",
             score);

    Vector2 score_font_size =
        MeasureTextEx(*font, score_str, SCOREBOARD_UI_PLAYER_SCORE_FONT_SIZE,
                      SCOREBOARD_UI_PLAYER_FONT_SPACE);
    Vector2 score_font_point = (Vector2){
        .x = is_player_1
                 ? name_point.x + name_font_size.x +
                       SCOREBOARD_UI_SPACE_BETWEEN_NAME_AND_SCORE
                 : name_point.x - SCOREBOARD_UI_SPACE_BETWEEN_NAME_AND_SCORE -
                       score_font_size.x,
        .y = container->y + ((container->height - score_font_size.y) / 2),
    };
    DrawTextEx(*font, score_str, score_font_point,
               SCOREBOARD_UI_PLAYER_SCORE_FONT_SIZE,
               SCOREBOARD_UI_PLAYER_FONT_SPACE, color);
}

///
///
///
Rectangle SB_redraw(const Scoreboard *sb) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    //
    // Outside border
    //
    Rectangle rect = (Rectangle){
        .x = SCOREBOARD_UI_PADDING,
        .y = SCOREBOARD_UI_PADDING,
        .width = screen_width - 2 * SCOREBOARD_UI_PADDING,
        .height = (float)screen_height *
                  (SCOREBOARD_UI_BORDER_HEIGHT_PERCENT / (float)100),
    };

    // TraceLog(LOG_DEBUG, ">>> [ SB_redraw ] - rect: %f, %f, %f, %f", rect.x,
    // rect.y, rect.width, rect.height);

    DrawRectangleLinesEx(rect, SCOREBOARD_UI_BORDER_THICKNESS,
                         SCOREBOARD_UI_BORDER_COLOR);

    //
    // `VS`
    //
    Font font = GetFontDefault();
    Vector2 vs_font_size = MeasureTextEx(font, "VS", SCOREBOARD_UI_VS_FONT_SIZE,
                                         SCOREBOARD_UI_VS_FONT_SPACE);
    // TraceLog(LOG_DEBUG, ">>> [ SB_redraw ] - vs_font_size: %f, %f",
    // vs_font_size.x, vs_font_size.y);

    float vs_font_draw_x = rect.x + ((rect.width - vs_font_size.x) / 2);
    float vs_font_draw_y = rect.y + ((rect.height - vs_font_size.y) / 2);
    Vector2 vs_font_point = (Vector2){
        .x = vs_font_draw_x,
        .y = vs_font_draw_y,
    };
    DrawTextEx(font, "VS", vs_font_point, SCOREBOARD_UI_VS_FONT_SIZE,
               SCOREBOARD_UI_VS_FONT_SPACE, SCOREBOARD_UI_BORDER_COLOR);
    // TraceLog(LOG_DEBUG, ">>> [ SB_redraw ] - vs_font_point: %f, %f",
    // vs_font_point.x, vs_font_point.y);

    //
    // Player
    //
    draw_player_name_and_score(sb->player_1_name, sb->player_1_score, true,
                               &font, &rect, SCOREBOARD_UI_BORDER_COLOR);
    draw_player_name_and_score(sb->player_2_name, sb->player_2_score, false,
                               &font, &rect, SCOREBOARD_UI_BORDER_COLOR);

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
