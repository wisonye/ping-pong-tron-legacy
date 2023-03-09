#include "player.h"

#include "stdlib.h"

///
///
///
Player *Player_create(const char *name, u8 score) {
    Player *player = malloc(sizeof(Player));
    *player = (Player){.name = name, .score = score};
    return player;
}

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
