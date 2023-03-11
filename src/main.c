#include <raylib.h>
#include <stdbool.h>
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
    (Color) { .r = 0x23, .g = 0x21, .b = 0x1B, .a = 0xFF }
#define TRON_LIGHT_BLUE \
    (Color) { .r = 0xAC, .g = 0xE6, .b = 0xFE, .a = 0xFF }
#define TRON_BLUE \
    (Color) { .r = 0x6F, .g = 0xC3, .b = 0xDF, .a = 0xFF }
#define TRON_YELLOW \
    (Color) { .r = 0xFF, .g = 0xE6, .b = 0x4D, .a = 0xFF }
#define TRON_ORANGE \
    (Color) { .r = 0xFF, .g = 0x9F, .b = 0x1C, .a = 0xFF }
#define TRON_RED \
    (Color) { .r = 0xF4, .g = 0x47, .b = 0x47, .a = 0xFF }

//
// UI
//
#define GAME_UI_INIT_SCREEN_WIDTH 1024
#define GAME_UI_INIT_SCREEN_HEIGHT 768
#define GAME_UI_PADDING 10.0f
#define GAME_UI_BACKGROUND_COLOR TRON_DARK
#define GAME_UI_BORDER_COLOR TRON_LIGHT_BLUE
#define GAME_UI_BALL_COLOR TRON_LIGHT_BLUE
#define GAME_UI_BALL_RADIUS 20.0f
#define GAME_UI_BALL_SPEED_X 400.0f
#define GAME_UI_BALL_SPEED_Y 400.0f
#define GAME_UI_RACKET_COLOR TRON_ORANGE
#define GAME_UI_BEFORE_START_BORDER_COLOR TRON_ORANGE
#define GAME_UI_BEFORE_START_TEXT_COLOR TRON_ORANGE

///
///
///
int main(void) {
    //
    // Try to get both 2 player names from env. If not exists, then use the
    // default names.
    //
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
        .table_rect =
            (Rectangle){
                .x = -1,
                .y = -1,
                .width = -1,
                .height = -1,
            },
        .ball =
            (Ball){
                .center = (Vector2){.x = -1.0f, .y = -1.0f},
                .radius = GAME_UI_BALL_RADIUS,
                .color = GAME_UI_BALL_COLOR,
                .speed_x = GAME_UI_BALL_SPEED_X,
                .speed_y = GAME_UI_BALL_SPEED_Y,

                //
                // `alpha_mask` is a black and white color image that uses for
                // blending operations, it HAS TO be created after the
                // `InitWindow` call. That means it creates inside
                // `Game_init()`, not here!!!
                //
                // .alpha_mask = ball_texture,
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
                .before_start_border_color = GAME_UI_BEFORE_START_BORDER_COLOR,
                .before_start_text_color = GAME_UI_BEFORE_START_TEXT_COLOR,
            },
        .state = GS_INIT,
    };

    //
    // Init and run the game
    //
    Game_init(&game);
    Game_run(&game);

    //
    // Make sure to unload resources!!!
    //
    // UnloadTexture(ball_texture);

    return 0;
}
