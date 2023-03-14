#ifndef __UTILS_H__
#define __UTILS_H__

#include <raylib.h>
#include "data_types.h"
#include "player.h"

///
///
///
void Utils_get_color_string(Color color, char *out_buffer, usize buffer_size);

///
///
///
void Utils_get_player_string(Player *player, char *out_buffer, usize buffer_size);

#endif
