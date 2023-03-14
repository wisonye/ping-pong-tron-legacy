#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "config.h"
#include "data_types.h"
#include "racket.h"

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

#endif
