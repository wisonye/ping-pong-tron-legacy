#include "game.h"

#include "raylib.h"

#define INIT_SCREEN_WIDTH 1024
#define INIT_SCREEN_HEIGHT 768

///
///
///
void Game_init(void) {
    InitWindow(INIT_SCREEN_WIDTH, INIT_SCREEN_HEIGHT, "Ping pong tron legacy");

    // Set our game FPS (frames-per-second)
    SetTargetFPS(120);

    // Set tracing log level
    SetTraceLogLevel(LOG_DEBUG);

    TraceLog(LOG_DEBUG, ">>> [ Game_init ] - Game initialization [ done ]");
}

///
///
///
void Game_run(void) {
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
void Game_pause(void) {}

///
///
///
void Game_resume(void) {}
