#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "ball.h"
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
// Game misc settings
//
#define GAME_FPS 60

//
// Game UI settings
//
#define GAME_UI_INIT_SCREEN_WIDTH 1024
#define GAME_UI_INIT_SCREEN_HEIGHT 768
#define GAME_UI_PADDING 10.0f
#define GAME_UI_BACKGROUND_COLOR TRON_DARK
#define GAME_UI_BORDER_COLOR TRON_LIGHT_BLUE
#define GAME_UI_RACKET_COLOR TRON_ORANGE

//
// Table UI settings
//
#define TABLE_UI_BORDER_COLOR TRON_LIGHT_BLUE
#define TABLE_UI_BORDER_THICKNESS 2.0f
#define TABLE_UI_BEFORE_START_BORDER_COLOR TRON_ORANGE
#define TABLE_UI_BEFORE_START_TEXT_COLOR TRON_ORANGE
#define TABLE_UI_START_PROMPT_TEXT "Press 'Space' to start the game"
#define TABLE_UI_START_PROMPT_FONT_SIZE 40.0f
#define TABLE_UI_START_PROMPT_FONT_SPACE 5.0f
#define TABLE_UI_START_PROMPT_CONTAINER_HORIZONTAL_PADDING 20.0f
#define TABLE_UI_START_PROMPT_CONTAINER_VERTICAL_PADDING 10.0f

//
// Ball UI settings
//
#define BALL_UI_BALL_COLOR TRON_LIGHT_BLUE
#define BALL_UI_FIREBALL_COLOR TRON_ORANGE
#define BALL_UI_BALL_RADIUS 20.0f
#define BALL_UI_BALL_VELOCITY_X 400.0f
#define BALL_UI_BALL_VELOCITY_Y 400.0f
// Init `alpha` value, it affects how light the particle at the beginning
#define BALL_UI_LIGHT_TRAIL_PRATICLE_INIT_ALPHA 0.8f
// It affects how big the particle will be: how many percentage of the ball
// size: 0.0 ~ 1.0 (0 ~ 100%)
#define BALL_UI_LIGHT_TRAIL_PRATICLE_SIZE 0.6f
// How many hits before increasing the ball velocity
#define BALL_UI_HITS_BEFORE_INCREASE_VELOCITY 2
// How many velocities increase to enable a fireball
#define BALL_UI_VELOCITIES_INCREASE_TO_ENABLE_FIREBALL 4
// Velocity acceleration
#define BALL_UI_VELOCITY_ACCELERATION 100

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
