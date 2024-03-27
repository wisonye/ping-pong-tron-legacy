#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <raylib.h>

#include "config.h"
#include "data_types.h"

///
///
///
typedef enum {
    PT_LEFT,
    PT_RIGHT,
} PlayerType;

///
///
///
typedef enum {
    RUT_MOVE_UP,
    RUT_MOVE_DOWN,
    RUT_RESET,
} RacketUpdateType;

///
///
///
typedef struct {
    Color color;
    Rectangle rect;
    Texture2D rect_texture;
} Racket;

///
///
///
typedef struct {
    PlayerType type;
    const char *name;
    usize score;
    usize level;
    // The default one
    Racket default_racket;
    // Player may have many rackets after level-up
    Racket rackets[RACKET_UI_MAX_RACKETS_PER_PLAYER];
} Player;

///
///
///
void Player_win(Player *player);

///
///
///
void Player_lose(Player *player);

///
///
///
void Player_racket_redraw(Player *player);

///
///
///
void Player_update_racket_after_screen_size_changed(Player *player,
                                                    Rectangle *container,
                                                    Rectangle *old_container);

///
///
///
void Player_update_racket(Player *player,
                          Rectangle *container,
                          RacketUpdateType rut);

#endif
