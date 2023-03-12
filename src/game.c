#include "game.h"

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "ball.h"
#include "player.h"
#include "scoreboard.h"
#include "table.h"

bool IS_FULLSCREEN = false;

///
///
///
void toggle_fullscreen(Game *game) {
    if (!IS_FULLSCREEN) {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
        IS_FULLSCREEN = true;
    } else {
        ToggleFullscreen();
        SetWindowSize(game->ui_settings.init_screen_width,
                      game->ui_settings.init_screen_height);
        IS_FULLSCREEN = false;
    }
}

///
///
///
// void reset

///
///
///
void Game_init(Game *game) {
    InitWindow(game->ui_settings.init_screen_width,
               game->ui_settings.init_screen_height, "Ping pong tron legacy");

    // Window states: No frame and buttons
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    // Set our game FPS (frames-per-second)
    SetTargetFPS(game->misc_settings.game_fps);

    // Initialize audio device
    InitAudioDevice();

    // Load sound effects
    game->ball.enable_fireball_sound_effect =
        LoadSound("resources/enable_fireball.wav");

    // Set tracing log level
    SetTraceLogLevel(LOG_DEBUG);

    Game_print_debug_info(game);

    // Hide the cursor
    HideCursor();

    // Set to `GS_BEFORE_START`
    game->state = GS_BEFORE_START;

    //
    // As I want to draw the ball with gradient visual effects (like a halo)
    // and a lighting trail that follows the moving ball, that's why do I need
    // to create an alpha mask image (with black and white color) as the
    // blending mask.
    //
    // - The `density` affects the halo border length!!!
    //
    // - The size of the alpha mask must be the same size of the ball
    //
    // - The lighting tail is just a bunch of particle instances, each particle
    //   has the init alpha value and size, and the size should be smaller than
    //   the ball to make it looks nicer.
    //
    float density = 0.5f;
    Image ball_alpha_mask_image = GenImageGradientRadial(
        game->ball.radius * 2, game->ball.radius * 2, density, WHITE, BLACK);
    Texture2D ball_texture = LoadTextureFromImage(ball_alpha_mask_image);
    UnloadImage(ball_alpha_mask_image);
    game->ball.alpha_mask = ball_texture;

    TraceLog(LOG_DEBUG, ">>> [ Game_init ] - Game initialization [ done ]");
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
    Rectangle table_rect = Table_redraw(game, &sb_rect);

    //
    // Ball
    //
    const Ball *ball = &game->ball;
    Ball_redraw(ball);

    //
    // Update `game->table_rect` if changed
    //
    // TraceLog(LOG_DEBUG,
    //          ">>> [ Game_redraw ] - table_rect: {x: %.2f, y: %.2f, width: "
    //          "%.2f, height: %.2f}",
    //          table_rect.x, table_rect.y, table_rect.width,
    //          table_rect.height);
    if (table_rect.x != game->table_rect.x ||
        table_rect.y != game->table_rect.y ||
        table_rect.width != game->table_rect.width ||
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
    // Press 'ctrl+f' to toggle fullscreen
    //
    if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_F)) {
        toggle_fullscreen(game);
        TraceLog(LOG_DEBUG,
                 ">>> [ Game_logic ] - Toggle fullscreen, screen_width: %d, "
                 "screen_height: %d",
                 GetScreenWidth(), GetScreenHeight());
    }

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
        // Update ball
        Ball_update(ball, &game->table_rect);

        // Update lighting tail
        Ball_update_lighting_tail(ball);

        /* TraceLog(LOG_DEBUG, */
        /*          ">>> [ Game_logic ] - ball center: { x: %.2f, y: %.2f, " */
        /*          "speed_x: %.2f, speed_Y: %.2f}", */
        /*          ball->center.x, ball->center.y, ball->speed_x,
         * ball->speed_y); */
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
        //
        // Update game logic
        //
        Game_logic(game);

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

    UnloadTexture(game->ball.alpha_mask);
    UnloadSound(game->ball.enable_fireball_sound_effect);  // Unload sound data
    CloseAudioDevice();

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
