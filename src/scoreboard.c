#include "scoreboard.h"

#include <stdlib.h>

///
///
///
Scoreboard *SB_create(u8 player_1_score, u8 player_2_score,
                      const char *player_1_name, const char *player_2_name) {
    Scoreboard *sb = malloc(sizeof(Scoreboard));

    *sb = (Scoreboard){
        .player_1_score = 0,
        .player_2_score = 0,
        .player_1_name = player_1_name,
        .player_2_name = player_2_name,
    };

    return sb;
}

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
