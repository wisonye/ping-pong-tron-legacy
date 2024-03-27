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
    GS_UNINIT       = 0x01,
    GS_INIT         = 0x02,
    GS_BEFORE_START = 0x03,
    GS_PLAYING      = 0x04,
    GS_PLAYER_WINS  = 0x05,
    GS_PAUSE        = 0x06,
} GameState;

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
    Player player1;
    Player player2;
    Scoreboard scoreboard;
    Rectangle table_rect_before_screen_changed;
    Rectangle table_rect;
    Ball ball;
    GameState state;
    bool is_fullscreen;
    bool is_player1_wins_last_round;
    Sound you_win_sound_effect;
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
void Game_pause(void);

///
///
///
void Game_resume(void);

///
///
///
void Game_print_debug_info(Game *game);

#endif
