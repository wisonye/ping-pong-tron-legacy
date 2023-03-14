#include "player.h"

#include <raylib.h>
#include <stdlib.h>

///
///
///
void Player_win(Player *player) {
    if (player == NULL) return;

    player->score += 1;
}

///
///
///
void Player_lose(Player *player) {
    if (player == NULL) return;

    player->score = player->score - 1 < 0 ? 0 : player->score - 1;
}

///
///
///
void Player_racket_redraw(Player *player, Rectangle *container) {
    if (player == NULL) return;

    DrawRectangleRec(player->default_racket.rect, player->default_racket.color);
}

///
///
///
void Player_update_racket_after_screen_size_changed(Player *player,
                                                    Rectangle *container,
                                                    Rectangle *old_container) {
    float old_y = player->default_racket.rect.y;
    float ratio_y = old_y / old_container->height;

    player->default_racket.rect.x =
        player->type == PT_LEFT ? container->x + RACKET_UI_MARGIN
                                : container->x + container->width -
                                      RACKET_UI_MARGIN - RACKET_UI_WIDTH;
    player->default_racket.rect.y = container->height * ratio_y;
}

///
///
///
void Player_update_racket(Player *player, Rectangle *container,
                          bool is_fullscreen, RacketUpdateType rut) {
    if (player == NULL) return;

    switch (rut) {
        //
        // Center `y`
        //
        case RUT_RESET:
            player->default_racket.rect = (Rectangle){
                .x = player->type == PT_LEFT
                         ? container->x + RACKET_UI_MARGIN
                         : container->x + container->width - RACKET_UI_MARGIN -
                               RACKET_UI_WIDTH,
                .y =
                    container->y + ((container->height - RACKET_UI_HEIGHT) / 2),
                .width = RACKET_UI_WIDTH,
                .height = RACKET_UI_HEIGHT,
            };
            TraceLog(LOG_DEBUG, "[ Player_update_racket ] - RUT_RESET");
            break;
        //
        // Apply velocity to `y`
        //
        case RUT_MOVE_UP:
            player->default_racket.rect.y = player->default_racket.rect.y -
                                            RACKET_UI_VELOCITY * GetFrameTime();
            break;
        case RUT_MOVE_DOWN:
            player->default_racket.rect.y = player->default_racket.rect.y +
                                            RACKET_UI_VELOCITY * GetFrameTime();
            break;
        default: {
        }
    }
}
