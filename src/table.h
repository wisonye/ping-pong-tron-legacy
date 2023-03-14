#ifndef __TABLE_H__
#define __TABLE_H__

#include <raylib.h>

#include "data_types.h"
#include "game.h"

///
///
///
// typedef struct Table {
//     Color border_color;
// } Table;

///
///
///
Rectangle Table_recalculate_rect(const Game *game, const Rectangle *sb_rect);

///
///
///
Rectangle Table_redraw(const Game *game, const Rectangle *sb_rect);

#endif
