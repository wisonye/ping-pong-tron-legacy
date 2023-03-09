#ifndef __GAME_H__
#define __GAME_H__

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
typedef struct {
    Player *player_1;
    Player *player_2;
    Scoreboard *scoreboard;
    /* Table table; */
    /* Ball ball; */
    GameState state;
} Game;

///
///
///
Game *Game_init(const char *player_1_name, const char *player_2_name);

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
