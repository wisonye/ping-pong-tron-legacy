#include <stdio.h>

#include "game.h"

#define player_1_name "Player 1"
#define player_2_name "Player 2"

int main(void) {
    Game *game = Game_init(player_1_name, player_2_name);
    Game_run(game);

    return 0;
}
