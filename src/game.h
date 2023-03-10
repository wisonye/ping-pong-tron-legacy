#ifndef __GAME_H__
#define __GAME_H__

#include <raylib.h>

#include "player.h"
#include "scoreboard.h"

///
///
///
typedef enum GameState {
    GS_UNINIT = 0x00,
    GS_INIT = 0x01,
    GS_RUNNING = 0x02,
    GS_PAUSE = 0x03,
} GameState;

///
///
///
typedef struct UiSettings {
    float padding;
    Color background_color;
} UiSettings;

///
///
///
typedef struct {
    Player player_1;
    Player player_2;
    Scoreboard scoreboard;
    /* Table table; */
    /* Ball ball; */
    GameState state;
    UiSettings ui_settings;
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
