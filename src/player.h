#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "data_types.h"

///
///
///
typedef struct Player {
    const char *name;
    u8 score;
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
