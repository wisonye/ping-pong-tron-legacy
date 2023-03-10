#include "player.h"

#include <stdlib.h>

///
///
///
void Player_win(Player *player) {
    if (player == NULL) return;

    player->score += 1;
}

///
///
///
void Player_lose(Player *player) {
    if (player == NULL) return;

    if (player->score - 1 >= 0) {
        player->score -= 1;
    }
}
