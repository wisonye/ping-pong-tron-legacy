#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <raylib.h>

#include "data_types.h"
#include "player.h"

///
///
///
typedef struct Scoreboard {
    Player *player1;
    Player *player2;
} Scoreboard;

///
///
///
Rectangle SB_redraw(const Scoreboard *sb);

///
///
///
Rectangle SB_recalculate_rect(void);

///
///
///
void SB_update_player_1_score(Scoreboard *sb, usize score);

///
///
///
void SB_update_player_2_score(Scoreboard *sb, usize score);

#endif
