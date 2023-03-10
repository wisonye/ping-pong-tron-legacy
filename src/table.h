#ifndef __TABLE_H__
#define __TABLE_H__

#include <raylib.h>
#include <stdint.h>

#include "data_types.h"

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
void Table_redraw(const Rectangle *sb_rect, const float ui_padding,
                  Color border_color);

#endif
