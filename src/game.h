#ifndef __GAME_H__
#define __GAME_H__

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
    /* player_1: Player; */
    /* player_2: Player; */
    /* Scoreboard scoreboard; */
    /* Table table; */
    /* Ball ball; */
    GameState state;
} Game;

///
///
///
Game *Game_init(void);

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

#endif
