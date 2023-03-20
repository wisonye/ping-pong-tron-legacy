#include "table.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "ball.h"
#include "config.h"
#include "game.h"
#include "player.h"

///
///
///
Rectangle Table_recalculate_rect(const Rectangle *sb_rect) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    //
    // Outside border
    //
    float sb_rect_bottom = sb_rect->y + sb_rect->height;
    Rectangle rect = (Rectangle){
        .x = TABLE_UI_MARGIN,
        .y = sb_rect_bottom + TABLE_UI_MARGIN,
        .width = screen_width - 2 * TABLE_UI_MARGIN,
        .height = (float)screen_height - sb_rect_bottom - 2 * TABLE_UI_MARGIN,
    };

    return rect;
}

///
///
///
Rectangle Table_redraw(const Game *game, const Rectangle *sb_rect) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    Font font = GetFontDefault();

    //
    // Outside border
    //
    float sb_rect_bottom = sb_rect->y + sb_rect->height;
    Rectangle rect = (Rectangle){
        .x = TABLE_UI_MARGIN,
        .y = sb_rect_bottom + TABLE_UI_MARGIN,
        .width = screen_width - 2 * TABLE_UI_MARGIN,
        .height = (float)screen_height - sb_rect_bottom - 2 * TABLE_UI_MARGIN,
    };

    DrawRectangleLinesEx(rect, TABLE_UI_BORDER_THICKNESS,
                         TABLE_UI_BORDER_COLOR);

    //
    // GS_BEFORE_START
    //
    if (game->state == GS_BEFORE_START) {
        // outside border
        Vector2 start_prompt_font_size =
            MeasureTextEx(font, TABLE_UI_FIRST_START_PROMPT_TEXT,
                          TABLE_UI_FIRST_START_PROMPT_FONT_SIZE,
                          TABLE_UI_FIRST_START_PROMPT_FONT_SPACE);

        float start_prompt_rect_width =
            start_prompt_font_size.x +
            2 * TABLE_UI_FIRST_START_PROMPT_CONTAINER_HORIZONTAL_PADDING;
        float start_prompt_rect_height =
            start_prompt_font_size.y +
            2 * TABLE_UI_FIRST_START_PROMPT_CONTAINER_VERTICAL_PADDING;
        Rectangle start_prompt_rect = (Rectangle){
            .x = rect.x + ((rect.width - start_prompt_rect_width) / 2),
            .y = rect.y + ((rect.height - start_prompt_rect_height) / 2),
            .width = start_prompt_rect_width,
            .height = start_prompt_rect_height,
        };
        DrawRectangleLinesEx(start_prompt_rect, TABLE_UI_BORDER_THICKNESS,
                             TABLE_UI_FIRST_START_PROMPT_BORDER_COLOR);

        // Text
        float start_prompt_font_draw_x =
            start_prompt_rect.x +
            TABLE_UI_FIRST_START_PROMPT_CONTAINER_HORIZONTAL_PADDING;
        float start_prompt_font_draw_y =
            start_prompt_rect.y +
            TABLE_UI_FIRST_START_PROMPT_CONTAINER_VERTICAL_PADDING;
        Vector2 start_prompt_font_point = (Vector2){
            .x = start_prompt_font_draw_x,
            .y = start_prompt_font_draw_y,
        };
        DrawTextEx(font, TABLE_UI_FIRST_START_PROMPT_TEXT,
                   start_prompt_font_point,
                   TABLE_UI_FIRST_START_PROMPT_FONT_SIZE,
                   TABLE_UI_FIRST_START_PROMPT_FONT_SPACE,
                   TABLE_UI_FIRST_START_PROMPT_TEXT_COLOR);
    }
    //
    // GS_PLAYER_WINS
    //
    else if (game->state == GS_PLAYER_WINS) {
        // Last winner's name
        char last_winner_name[100] = {0};
        snprintf(last_winner_name, sizeof(last_winner_name), "%s%s",
                 (game->is_player1_wins_last_round) ? game->player1.name
                                                    : game->player2.name,
                 TABLE_UI_PLAYER_WINS_PROMPT_TEXT);

        // outside border
        Vector2 win_prompt_font_size = MeasureTextEx(
            font, last_winner_name, TABLE_UI_PLAYER_WINS_PROMPT_FONT_SIZE,
            TABLE_UI_PLAYER_WINS_PROMPT_FONT_SPACE);

        Vector2 restart_font_size =
            MeasureTextEx(font, TABLE_UI_PLAYER_WINS_RESTART_TEXT,
                          TABLE_UI_PLAYER_WINS_RESTART_FONT_SIZE,
                          TABLE_UI_PLAYER_WINS_RESTART_FONT_SPACE);

        float wins_prompt_rect_width =
            win_prompt_font_size.x +
            2 * TABLE_UI_PLAYER_WINS_PROMPT_CONTAINER_HORIZONTAL_PADDING;
        float wins_prompt_rect_height =
            win_prompt_font_size.y + restart_font_size.y +
            2 * TABLE_UI_PLAYER_WINS_PROMPT_CONTAINER_VERTICAL_PADDING +
            2 * TABLE_UI_PLAYER_WINS_RESTART_CONTAINER_VERTICAL_PADDING;
        Rectangle wins_prompt_rect = (Rectangle){
            .x = rect.x + ((rect.width - wins_prompt_rect_width) / 2),
            .y = rect.y + ((rect.height - wins_prompt_rect_height) / 2),
            .width = wins_prompt_rect_width,
            .height = wins_prompt_rect_height,
        };
        DrawRectangleLinesEx(wins_prompt_rect, TABLE_UI_BORDER_THICKNESS,
                             TABLE_UI_PLAYER_WINS_PROMPT_BORDER_COLOR);

        // Text
        float wins_prompt_font_draw_x =
            wins_prompt_rect.x +
            TABLE_UI_PLAYER_WINS_PROMPT_CONTAINER_HORIZONTAL_PADDING;
        float wins_prompt_font_draw_y =
            wins_prompt_rect.y +
            TABLE_UI_PLAYER_WINS_PROMPT_CONTAINER_VERTICAL_PADDING;
        Vector2 wins_prompt_font_point = (Vector2){
            .x = wins_prompt_font_draw_x,
            .y = wins_prompt_font_draw_y,
        };
        DrawTextEx(font, last_winner_name, wins_prompt_font_point,
                   TABLE_UI_PLAYER_WINS_PROMPT_FONT_SIZE,
                   TABLE_UI_PLAYER_WINS_PROMPT_FONT_SPACE,
                   TABLE_UI_PLAYER_WINS_PROMPT_TEXT_COLOR);

        float restart_font_draw_x =
            wins_prompt_rect.x +
            ((wins_prompt_rect.width - restart_font_size.x) / 2);
        float restart_font_draw_y =
            wins_prompt_font_draw_y + win_prompt_font_size.y +
            TABLE_UI_PLAYER_WINS_PROMPT_CONTAINER_VERTICAL_PADDING;
        Vector2 restart_font_point = (Vector2){
            .x = restart_font_draw_x,
            .y = restart_font_draw_y,
        };
        DrawTextEx(font, TABLE_UI_PLAYER_WINS_RESTART_TEXT, restart_font_point,
                   TABLE_UI_PLAYER_WINS_RESTART_FONT_SIZE,
                   TABLE_UI_PLAYER_WINS_RESTART_FONT_SPACE,
                   TABLE_UI_PLAYER_WINS_RESTART_TEXT_COLOR);
    }

    return rect;
}
