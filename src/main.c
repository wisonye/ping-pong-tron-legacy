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
                .radius = BALL_UI_BALL_RADIUS,
                .color = BALL_UI_BALL_COLOR,
                .fireball_color = BALL_UI_FIREBALL_COLOR,
                .velocity_x = BALL_UI_BALL_VELOCITY_X,
                .velocity_y = BALL_UI_BALL_VELOCITY_Y,
                .hits_before_increase_velocity =
                    BALL_UI_HITS_BEFORE_INCREASE_VELOCITY,
                .velocities_increase_to_enable_fireball =
                    BALL_UI_VELOCITIES_INCREASE_TO_ENABLE_FIREBALL,
                .velocity_acceleration = BALL_UI_VELOCITY_ACCELERATION,
                .enabled_fireball = false,
                .lighting_tail =
                    (BallLightingTail){
                        .particle_init_alpha =
                            BALL_UI_LIGHT_TRAIL_PRATICLE_INIT_ALPHA,
                        .particle_size = BALL_UI_LIGHT_TRAIL_PRATICLE_SIZE,
                    },

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
                .table_ui =
                    (TableUiSettings){
                        .margin = GAME_UI_PADDING,
                        .border_color = TABLE_UI_BORDER_COLOR,
                        .border_thickness = TABLE_UI_BORDER_THICKNESS,
                        .start_prompt_border_color =
                            TABLE_UI_BEFORE_START_BORDER_COLOR,
                        .start_prompt_text_color =
                            TABLE_UI_BEFORE_START_TEXT_COLOR,
                        .start_prompt_text = TABLE_UI_START_PROMPT_TEXT,
                        .start_prompt_font_size =
                            TABLE_UI_START_PROMPT_FONT_SIZE,
                        .start_prompt_font_space =
                            TABLE_UI_START_PROMPT_FONT_SPACE,
                        .start_prompt_container_horizontal_padding =
                            TABLE_UI_START_PROMPT_CONTAINER_HORIZONTAL_PADDING,
                        .start_prompt_container_vertical_padding =
                            TABLE_UI_START_PROMPT_CONTAINER_VERTICAL_PADDING,
                    },
                .racket_ui =
                    (RacketUiSettings){
                        .racket_color = GAME_UI_RACKET_COLOR,
                    }},
        .misc_settings =
            (MiscSettings){
                .game_fps = GAME_FPS,
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
