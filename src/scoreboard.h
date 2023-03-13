#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <raylib.h>

#include "data_types.h"

///
///
///
typedef struct Scoreboard {
    usize player_1_score;
    usize player_2_score;
    const char *player_1_name;
    const char *player_2_name;
} Scoreboard;

///
///
///
Rectangle SB_redraw(const Scoreboard *sb);

///
///
///
void SB_update_player_1_score(Scoreboard *sb, usize score);

///
///
///
void SB_update_player_2_score(Scoreboard *sb, usize score);

#endif
