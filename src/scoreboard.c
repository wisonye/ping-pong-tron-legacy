#include "scoreboard.h"

#include <raylib.h>

#define BORDER_HEIGHT_PERCENT 10
#define BORDER_THICKNESS 2.0f

///
///
///
void SB_redraw(Scoreboard *sb, const float ui_padding, Color border_color) {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    Rectangle rect = (Rectangle){
        .x = ui_padding,
        .y = ui_padding,
        .width = screen_width - 2 * ui_padding,
        .height = (float)screen_height * ((float)BORDER_HEIGHT_PERCENT / 100),
    };

    /* TraceLog(LOG_DEBUG, ">>> [ SB_redraw ] - rect: %f, %f, %f, %f", rect.x,
     */
    /*          rect.y, rect.width, rect.height); */

    DrawRectangleLinesEx(rect, BORDER_THICKNESS, border_color);
}

///
///
///
void update_player_1_score(Scoreboard *sb, u8 score);

///
///
///
void update_player_2_score(Scoreboard *sb, u8 score);
