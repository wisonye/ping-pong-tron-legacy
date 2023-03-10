#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"

//
// Player
#define PLAYER_1_NAME "Player 1"
#define PLAYER_2_NAME "Player 2"

//
// Color theme
//
#define TRON_DARK \
    (Color) { .r = 0x23, .g = 0x21, .b = 0x1B, .a = 100 }
#define TRON_LIGHT_BLUE \
    (Color) { .r = 0xAC, .g = 0xE6, .b = 0xFE, .a = 100 }
#define TRON_BLUE \
    (Color) { .r = 0x6F, .g = 0xC3, .b = 0xDF, .a = 100 }
#define TRON_YELLOW \
    (Color) { .r = 0xFF, .g = 0xE6, .b = 0x4D, .a = 100 }
#define TRON_ORANGE \
    (Color) { .r = 0xFF, .g = 0x9F, .b = 0x1C, .a = 100 }
#define TRON_RED \
    (Color) { .r = 0xF4, .g = 0x47, .b = 0x47, .a = 100 }

//
// UI
//
#define GAME_UI_INIT_SCREEN_WIDTH 1024
#define GAME_UI_INIT_SCREEN_HEIGHT 768
#define GAME_UI_PADDING 10.0f
#define GAME_UI_BACKGROUND_COLOR TRON_DARK
#define GAME_UI_BORDER_COLOR TRON_LIGHT_BLUE
#define GAME_UI_BALL_COLOR TRON_LIGHT_BLUE
#define GAME_UI_RACKET_COLOR TRON_ORANGE

///
///
///
int main(void) {
    const char *player_1_name = getenv("PLAYER_1_NAME") != NULL
                                    ? getenv("PLAYER_1_NAME")
                                    : PLAYER_1_NAME;

    const char *player_2_name = getenv("PLAYER_2_NAME") != NULL
                                    ? getenv("PLAYER_2_NAME")
                                    : PLAYER_2_NAME;

    //
    // Create game instance
    //
    Game game = (Game){
        .player_1 = (Player){.name = player_1_name, .score = 188},
        .player_2 = (Player){.name = player_2_name, .score = 288},
        .scoreboard =
            (Scoreboard){
                .player_1_score = 188,
                .player_2_score = 288,
                .player_1_name = player_1_name,
                .player_2_name = player_2_name,
            },
        .ui_settings =
            (UiSettings){
                .init_screen_width = GAME_UI_INIT_SCREEN_WIDTH,
                .init_screen_height = GAME_UI_INIT_SCREEN_HEIGHT,
                .padding = GAME_UI_PADDING,
                .background_color = GAME_UI_BACKGROUND_COLOR,
                .border_color = GAME_UI_BORDER_COLOR,
                .ball_color = GAME_UI_BALL_COLOR,
                .racket_color = GAME_UI_RACKET_COLOR,
            },
        .state = GS_INIT,
    };

    //
    // Init and run the game
    //
    Game_init(&game);
    Game_run(&game);
}
