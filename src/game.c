#include "game.h"

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "scoreboard.h"
#include "table.h"

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

    // Set to `GS_BEFORE_START`
    game->state = GS_BEFORE_START;
}

///
///
///
void Game_redraw(Game *game) {
    //
    // Scoreboard
    //
    Rectangle sb_rect = SB_redraw(&game->scoreboard, game->ui_settings.padding,
                                  game->ui_settings.border_color);

    //
    // Table
    //
    Rectangle table_rect =
        Table_redraw(game, &sb_rect, game->ui_settings.padding,
                     game->ui_settings.border_color,
                     game->ui_settings.before_start_border_color,
                     game->ui_settings.before_start_text_color);

    //
    // Update `game->table_rect` if changed
    //
    if (table_rect.x != game->table_rect.x &&
        table_rect.y != game->table_rect.y &&
        table_rect.width != game->table_rect.width &&
        table_rect.height != game->table_rect.height) {
        game->table_rect = table_rect;

        TraceLog(LOG_DEBUG, ">>> [ Game_redraw ] - Update 'game->table_rect'");
    }
}

///
///
///
void Game_logic(Game *game) {
    //
    // Press 'space' to start game
    //
    if (IsKeyPressed(KEY_SPACE) && game->state == GS_BEFORE_START) {
        game->state = GS_PLAYING;
        Ball_restart(&game->ball, &game->table_rect);
        Game_print_debug_info(game);
    }

    if (game->state == GS_PLAYING) {
        Ball *ball = &game->ball;
        Rectangle *table_rect = &game->table_rect;

        //
        // Ball bouncing in the container
        //
        ball->center.x += GetFrameTime() * ball->speed_x;
        ball->center.y += GetFrameTime() * ball->speed_y;

        // If `ball` hit the bottom of `table_rect`
        if (ball->center.x - ball->radius <= table_rect->x) {
            ball->center.x = table_rect->x + ball->radius;
            ball->speed_x *= -1;  // Flip the speed_x direction
        }
        // If `ball` hit the top of `table_rect`
        else if (ball->center.x + ball->radius >=
                 table_rect->x + table_rect->width) {
            ball->center.x = table_rect->x + table_rect->width - ball->radius;
            ball->speed_x *= -1;  // Flip the speed_x direction
        }

        // If `ball` hit the left of `table_rect`
        if (ball->center.y - ball->radius <= table_rect->y) {
            ball->center.y = table_rect->y + ball->radius;
            ball->speed_y *= -1;  // Flip the speed_y direction
        }
        // If `ball` hit the right of `table_rect`
        else if (ball->center.y + ball->radius >=
                 table_rect->y + table_rect->height) {
            ball->center.y = table_rect->y + table_rect->height - ball->radius;
            ball->speed_y *= -1;  // Flip the speed_y direction
        }

        /* TraceLog(LOG_DEBUG, */
        /*          ">>> [ Game_logic ] - ball center: { x: %.2f, y: %.2f, " */
        /*          "speed_x: %.2f, speed_Y: %.2f}", */
        /*          ball->center.x, ball->center.y, ball->speed_x, ball->speed_y); */
    }
}

///
///
///
void Game_run(Game *game) {
    TraceLog(LOG_DEBUG, ">>> [ Game_run ] - Game is running");
    Game_print_debug_info(game);

    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        BeginDrawing();

        //
        // Clean last frame
        //
        ClearBackground(game->ui_settings.background_color);

        //
        // Game logic
        //
        Game_logic(game);

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
        case GS_BEFORE_START:
            strncpy(state_str, "GS_BEFORE_START", sizeof(state_str));
            break;
        case GS_PLAYING:
            strncpy(state_str, "GS_PLAYING", sizeof(state_str));
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
             "\tplayer1: {\n\t\tname: %s\n\t\tscore: %llu\n\t}",
             game->player_1.name, game->player_1.score);

    //
    // Player2
    //
    char player_2_str[100];
    snprintf(player_2_str, sizeof(player_2_str),
             "\tplayer2: {\n\t\tname: %s\n\t\tscore: %llu\n\t}",
             game->player_2.name, game->player_2.score);

    //
    // Ball
    //
    char ball_str[200];
    snprintf(
        ball_str, sizeof(ball_str),
        "\tball: {\n\t\tcenter: { x: %.2f, y: %.2f }\n\t\tradius: %.2f\n\t}",
        game->ball.center.x, game->ball.center.y, game->ball.radius);

    //
    // Debug info
    //
    snprintf(debug_info, sizeof(debug_info), "\n{\n\tstate: %s\n%s\n%s\n%s\n}",
             state_str, player_1_str, player_2_str, ball_str);

    TraceLog(LOG_DEBUG, ">>> [ Game_Print_debug_info ] - %s", debug_info);
}
