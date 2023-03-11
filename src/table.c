#include "table.h"

#include <raylib.h>
#include <stdlib.h>

#include "ball.h"
#include "game.h"
#include "player.h"

///
///
///
Rectangle Table_redraw(const Game *game, const Rectangle *sb_rect) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    Font font = GetFontDefault();

    const TableUiSettings *table_ui = &game->ui_settings.table_ui;

    //
    // Outside border
    //
    float sb_rect_bottom = sb_rect->y + sb_rect->height;
    Rectangle rect = (Rectangle){
        .x = table_ui->margin,
        .y = sb_rect_bottom + table_ui->margin,
        .width = screen_width - 2 * table_ui->margin,
        .height = (float)screen_height - sb_rect_bottom - 2 * table_ui->margin,
    };

    DrawRectangleLinesEx(rect, table_ui->border_thickness,
                         table_ui->border_color);

    //
    // GS_BEFORE_START
    //
    if (game->state == GS_BEFORE_START) {
        // outside border
        Vector2 start_prompt_font_size = MeasureTextEx(
            font, table_ui->start_prompt_text, table_ui->start_prompt_font_size,
            table_ui->start_prompt_font_space);

        float start_prompt_rect_width =
            start_prompt_font_size.x +
            2 * table_ui->start_prompt_container_horizontal_padding;
        float start_prompt_rect_height =
            start_prompt_font_size.y +
            2 * table_ui->start_prompt_container_vertical_padding;
        Rectangle start_prompt_rect = (Rectangle){
            .x = rect.x + ((rect.width - start_prompt_rect_width) / 2),
            .y = rect.y + ((rect.height - start_prompt_rect_height) / 2),
            .width = start_prompt_rect_width,
            .height = start_prompt_rect_height,
        };
        DrawRectangleLinesEx(start_prompt_rect, table_ui->border_thickness,
                             table_ui->start_prompt_border_color);

        // Text
        float start_prompt_font_draw_x =
            start_prompt_rect.x +
            table_ui->start_prompt_container_horizontal_padding;
        float start_prompt_font_draw_y =
            start_prompt_rect.y +
            table_ui->start_prompt_container_vertical_padding;
        Vector2 start_prompt_font_point = (Vector2){
            .x = start_prompt_font_draw_x,
            .y = start_prompt_font_draw_y,
        };
        DrawTextEx(font, table_ui->start_prompt_text, start_prompt_font_point,
                   table_ui->start_prompt_font_size,
                   table_ui->start_prompt_font_space,
                   table_ui->start_prompt_text_color);
    }

    return rect;
}
