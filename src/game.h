#ifndef __GAME_H__
#define __GAME_H__


///
///
///
typedef enum GameState {
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
void Game_init(void);

///
///
///
void Game_run(void);

///
///
///
void Game_pause(void);

///
///
///
void Game_resume(void);

#endif
