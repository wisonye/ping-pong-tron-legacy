#include "table.h"

#include <raylib.h>
#include <stdlib.h>

#include "ball.h"
#include "game.h"
#include "player.h"

// Border
#define BORDER_THICKNESS 2.0f

// Before start
#define BEFORE_START_TEXT "Press 'Space' to start the game"
#define BEFORE_START_FONT_SIZE 40.0f
#define BEFORE_START_FONT_SPACE 5.0f
#define BEFORE_START_CONTAINER_HORIZONTAL_PADDING 20.0f
#define BEFORE_START_CONTAINER_VERTICAL_PADDING 10.0f

///
///
///
Rectangle Table_redraw(const Game *game, const Rectangle *sb_rect,
                       const float ui_padding, Color border_color,
                       Color before_start_border_color,
                       Color before_start_text_color) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    Font font = GetFontDefault();

    //
    // Outside border
    //
    float sb_rect_bottom = sb_rect->y + sb_rect->height;
    Rectangle rect = (Rectangle){
        .x = ui_padding,
        .y = sb_rect_bottom + ui_padding,
        .width = screen_width - 2 * ui_padding,
        .height = (float)screen_height - sb_rect_bottom - 2 * ui_padding,
    };

    DrawRectangleLinesEx(rect, BORDER_THICKNESS, border_color);

    //
    // GS_BEFORE_START
    //
    if (game->state == GS_BEFORE_START) {
        // outside border
        Vector2 before_start_font_size =
            MeasureTextEx(font, BEFORE_START_TEXT, BEFORE_START_FONT_SIZE,
                          BEFORE_START_FONT_SPACE);

        float before_start_rect_width =
            before_start_font_size.x +
            2 * BEFORE_START_CONTAINER_HORIZONTAL_PADDING;
        float before_start_rect_height =
            before_start_font_size.y +
            2 * BEFORE_START_CONTAINER_VERTICAL_PADDING;
        Rectangle before_start_rect = (Rectangle){
            .x = rect.x + ((rect.width - before_start_rect_width) / 2),
            .y = rect.y + ((rect.height - before_start_rect_height) / 2),
            .width = before_start_rect_width,
            .height = before_start_rect_height,
        };
        DrawRectangleLinesEx(before_start_rect, BORDER_THICKNESS,
                             before_start_border_color);

        // Text
        float before_start_font_draw_x =
            before_start_rect.x + BEFORE_START_CONTAINER_HORIZONTAL_PADDING;
        float before_start_font_draw_y =
            before_start_rect.y + BEFORE_START_CONTAINER_VERTICAL_PADDING;
        Vector2 before_start_font_point = (Vector2){
            .x = before_start_font_draw_x,
            .y = before_start_font_draw_y,
        };
        DrawTextEx(font, BEFORE_START_TEXT, before_start_font_point,
                   BEFORE_START_FONT_SIZE, BEFORE_START_FONT_SPACE,
                   before_start_text_color);
    }

    //
    // Ball
    //
    const Ball *ball = &game->ball;
    Ball_redraw(ball);

    return rect;
}
