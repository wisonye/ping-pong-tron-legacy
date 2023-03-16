#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ball.h"
#include "config.h"
#include "game.h"

///
/// All pre-defined macros are in `config.h`
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
        .player1 = (Player){.type = PT_LEFT,
                            .name = player_1_name,
                            .score = 0,
                            .rackets = {0},
                            .default_racket =
                                {
                                    .color = RACKET_UI_COLOR,
                                    .rect = {0},
                                    .rect_texture = {0},
                                }},
        .player2 = (Player){.type = PT_RIGHT,
                            .name = player_2_name,
                            .score = 0,
                            .rackets = {0},
                            .default_racket =
                                {
                                    .color = RACKET_UI_COLOR,
                                    .rect = {0},
                                    .rect_texture = {0},
                                }},
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
                .velocity_x = BALL_UI_BALL_VELOCITY_X,
                .velocity_y = BALL_UI_BALL_VELOCITY_Y,
                .current_hits = 0,
                .current_velocities_increase = 0,
                .enabled_fireball = false,
                .lighting_tail = (BallLightingTail){0},

                //
                // `alpha_mask` is a black and white color image that uses for
                // blending operations, it HAS TO be created after the
                // `InitWindow` call. That means it creates inside
                // `Game_init()`, not here!!!
                //
                // .alpha_mask = ball_texture,
            },
        .state = GS_INIT,
        .is_fullscreen = false,
        .is_player1_wins_last_round = false,
    };

    game.scoreboard.player1 = &game.player1;
    game.scoreboard.player2 = &game.player2;

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
