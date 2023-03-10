#include "game.h"

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "scoreboard.h"

GameState game_state = GS_UNINIT;

///
///
///
void Game_init(Game *game) {
    InitWindow(game->ui_settings.init_screen_width,
               game->ui_settings.init_screen_height, "Ping pong tron legacy");

    // Set our game FPS (frames-per-second)
    SetTargetFPS(120);

    // Set tracing log level
    SetTraceLogLevel(LOG_DEBUG);

    TraceLog(LOG_DEBUG, ">>> [ Game_init ] - Game initialization [ done ]");

    Game_print_debug_info(game);
}
///
///
///
void Game_redraw(Game *game) {
    SB_redraw(&game->scoreboard, game->ui_settings.padding);
}

///
///
///
void Game_run(Game *game) {
    TraceLog(LOG_DEBUG, ">>> [ Game_run ] - Game is running");
    game->state = GS_RUNNING;
    Game_print_debug_info(game);

    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        BeginDrawing();

        //
        // Clean last frame
        //
        ClearBackground(game->ui_settings.background_color);

        //
        // Redraw the entire game
        //
        Game_redraw(game);

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

///
///
///
void Game_print_debug_info(Game *game) {
    char debug_info[1024];

    //
    // Game state
    //
    char state_str[20] = {0};
    switch (game->state) {
        case GS_INIT:
            strncpy(state_str, "GS_INIT", sizeof(state_str));
            break;
        case GS_RUNNING:
            strncpy(state_str, "GS_RUNNING", sizeof(state_str));
            break;
        case GS_PAUSE:
            strncpy(state_str, "GS_PAUSE", sizeof(state_str));
            break;
        default:
            strncpy(state_str, "GS_UNINIT", sizeof(state_str));
    }

    //
    // Player1
    //
    char player_1_str[100];
    snprintf(player_1_str, sizeof(player_1_str),
             "\tplayer1: {\n\t\tname: %s\n\t\tscore: %u\n\t}",
             game->player_1.name, game->player_1.score);

    //
    // Player2
    //
    char player_2_str[100];
    snprintf(player_2_str, sizeof(player_2_str),
             "\tplayer2: {\n\t\tname: %s\n\t\tscore: %u\n\t}",
             game->player_2.name, game->player_2.score);

    //
    // Debug info
    //
    snprintf(debug_info, sizeof(debug_info), "\n{\n\tstate: %s\n%s\n%s\n}",
             state_str, player_1_str, player_2_str);

    TraceLog(LOG_DEBUG, ">>> [ Game_Print_debug_info ] - %s", debug_info);
}
