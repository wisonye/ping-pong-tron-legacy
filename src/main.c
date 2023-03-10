#include <raylib.h>
#include <stdio.h>

#include "game.h"

#define player_1_name "Player 1"
#define player_2_name "Player 2"
#define GAME_UI_PADDING 10.0f
#define GAME_UI_BACKGROUND_COLOR \
    (Color) { .r = 0x23, .g = 0x21, .b = 0x1B, .a = 100 }

///
///
///
int main(void) {
    //
    // Create game instance
    //
    Game game = (Game){
        .player_1 = Player_create(player_1_name, 0),
        .player_2 = Player_create(player_2_name, 0),
        .scoreboard = SB_create(0, 0, player_1_name, player_2_name),
        .ui_settings =
            (UiSettings){
                .padding = GAME_UI_PADDING,
                .background_color = GAME_UI_BACKGROUND_COLOR,
            },
        .state = GS_INIT,
    };

    //
    // Init and run the game
    //
    Game_init(&game);
    Game_run(&game);
}
