#ifndef __GAME_H__
#define __GAME_H__

#include <raylib.h>

#include "ball.h"
#include "player.h"
#include "scoreboard.h"

///
///
///
typedef enum {
    GS_UNINIT = 0x01,
    GS_INIT = 0x02,
    GS_BEFORE_START = 0x03,
    GS_PLAYING = 0x04,
    GS_PAUSE = 0x05,
} GameState;

///
///
///
typedef struct {
    Color racket_color;
} RacketUiSettings;

///
///
///
typedef struct {
    float margin;
    float border_thickness;
    Color border_color;
    Color start_prompt_border_color;
    Color start_prompt_text_color;
    const char *start_prompt_text;
    float start_prompt_font_size;
    float start_prompt_font_space;
    float start_prompt_container_horizontal_padding;
    float start_prompt_container_vertical_padding;
} TableUiSettings;

///
///
///
typedef struct {
    usize init_screen_width;
    usize init_screen_height;
    float padding;
    Color background_color;
    Color border_color;
    RacketUiSettings racket_ui;
    TableUiSettings table_ui;
} UiSettings;

///
///
///
typedef struct {
    usize game_fps;
} MiscSettings;

///
///
///
typedef struct {
    Player player_1;
    Player player_2;
    Scoreboard scoreboard;
    Rectangle table_rect;
    Ball ball;
    GameState state;
    UiSettings ui_settings;
    MiscSettings misc_settings;
} Game;

///
///
///
void Game_init(Game *game);

///
///
///
void Game_redraw(Game *game);

///
///
///
void Game_run(Game *game);

///
///
///
void Game_pause(Game *game);

///
///
///
void Game_resume(Game *game);

///
///
///
void Game_print_debug_info(Game *game);

#endif
