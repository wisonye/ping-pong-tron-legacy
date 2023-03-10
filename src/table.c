#include "table.h"

#include <raylib.h>

#include "player.h"

#define BORDER_THICKNESS 2.0f

///
///
///
void Table_redraw(const Rectangle *sb_rect, const float ui_padding,
                  Color border_color) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

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
}
