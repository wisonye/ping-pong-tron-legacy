#include "game.h"

#include <stdlib.h>

#include "raylib.h"

#define INIT_SCREEN_WIDTH 1024
#define INIT_SCREEN_HEIGHT 768

GameState game_state = GS_UNINIT;

///
///
///
Game *Game_init(void) {
    InitWindow(INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT, "Ping pong tron legacy");

    // Set our game FPS (frames-per-second)
    SetTargetFPS(120);

    // Set tracing log level
    SetTraceLogLevel(LOG_DEBUG);

    TraceLog(LOG_DEBUG, ">>> [ Game_init ] - Game initialization [ done ]");

    Game *game = malloc(sizeof(Game));
    *game = (Game){
        .state = GS_INIT,
    };

    return game;
}

///
///
///
void Game_run(Game *game) {
    TraceLog(LOG_DEBUG, ">>> [ Game_run ] - Game is running");

    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        BeginDrawing();

        //
        // Clean last frame
        //
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    TraceLog(LOG_DEBUG, ">>> [ Game_run ] - Exit the game loop");

    //
    // Close window and OpenGL context
    //
    CloseWindow();
}

///
///
///
void Game_pause(Game *game) {}

///
///
///
void Game_resume(Game *game) {}
