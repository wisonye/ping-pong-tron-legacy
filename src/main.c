#include <raylib.h>
#include <stdio.h>

#include "game.h"

#define PLAYER_1_NAME "Player 1"
#define PLAYER_2_NAME "Player 2"
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
        .player_1 = (Player){.name = PLAYER_1_NAME, .score = 0},
        .player_2 = (Player){.name = PLAYER_2_NAME, .score = 0},
        .scoreboard =
            (Scoreboard){
                .player_1_score = 0,
                .player_2_score = 0,
                .player_1_name = PLAYER_1_NAME,
                .player_2_name = PLAYER_2_NAME,
            },
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
