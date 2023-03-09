#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__

#include <stdint.h>

#include "data_types.h"

///
///
///
typedef struct Scoreboard {
    u8 player_1_score;
    u8 player_2_score;
    const char *player_1_name;
    const char *player_2_name;
} Scoreboard;

///
///
///
Scoreboard *SB_create(u8 player_1_score, u8 player_2_score,
                      const char *player_1_name, const char *player_2_name);

///
///
///
void SB_redraw(Scoreboard *sb);

///
///
///
void update_player_1_score(Scoreboard *sb, u8 score);

///
///
///
void update_player_2_score(Scoreboard *sb, u8 score);

#endif
