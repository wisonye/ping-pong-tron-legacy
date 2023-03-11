#ifndef __TABLE_H__
#define __TABLE_H__

#include <raylib.h>

#include "data_types.h"
#include "game.h"

///
///
///
typedef struct Table {
    usize player_1_score;
    usize player_2_score;
    const char *player_1_name;
    const char *player_2_name;
} Table;

///
///
///
Rectangle Table_redraw(const Game *game, const Rectangle *sb_rect);

#endif
