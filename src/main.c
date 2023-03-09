#include <stdio.h>

#include "game.h"

int main(void) {
    Game *game = Game_init();
    Game_run(game);

    return 0;
}
