#include "game.h"

#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "ball.h"
#include "config.h"
#include "player.h"
#include "scoreboard.h"
#include "table.h"
#include "utils.h"

///
///
///
void toggle_fullscreen(Game *game) {
    if (!game->is_fullscreen) {
        int monitor = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        ToggleFullscreen();
        game->is_fullscreen = true;
    } else {
        ToggleFullscreen();
        SetWindowSize(GAME_UI_INIT_SCREEN_WIDTH, GAME_UI_INIT_SCREEN_HEIGHT);
        game->is_fullscreen = false;
    }
}

///
///
///
void Game_init(Game *game) {
    InitWindow(GAME_UI_INIT_SCREEN_WIDTH, GAME_UI_INIT_SCREEN_HEIGHT,
               "Ping pong tron legacy");

    // Window states: No frame and buttons
    SetWindowState(FLAG_WINDOW_UNDECORATED);

    // Set our game FPS (frames-per-second)
    SetTargetFPS(GAME_FPS);

    // Initialize audio device
    InitAudioDevice();

    // Set tracing log level
    SetTraceLogLevel(LOG_DEBUG);

    //
    // Load sound effects
    //
    // game->you_win_sound_effect = Utils_load_sound(YOU_WIN_SOUND_EFFECT_1);
    game->you_win_sound_effect = Utils_load_sound(YOU_WIN_SOUND_EFFECT_2);
    game->ball.enable_fireball_sound_effect =
        Utils_load_sound(ENABLE_FIREBALL_SOUND_EFFECT);
    game->ball.enable_lightning_ball_sound_effect =
        Utils_load_sound(ENABLE_LIGHTNING_BALL_SOUND_EFFECT);
    game->ball.hit_racket_sound_effect =
        Utils_load_sound(BALL_HIT_RACKET_SOUND_EFFECT);

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
    game->ball.alpha_mask = LoadTextureFromImage(ball_alpha_mask_image);
    UnloadImage(ball_alpha_mask_image);

    //
    // Lightning ball
    //
    game->ball.lightning_ball = Utils_load_texture(BALL_UI_LIGHTNING_BALL);

    //
    // Racket gradient texture
    //
    Image racket_image = Utils_load_image(RACKET_UI_LASER_RACKET_TEXTURE);
    ImageResize(&racket_image, RACKET_UI_WIDTH, RACKET_UI_HEIGHT);
    game->player1.default_racket.rect_texture =
        LoadTextureFromImage(racket_image);
    game->player2.default_racket.rect_texture =
        LoadTextureFromImage(racket_image);
    UnloadImage(racket_image);

    TraceLog(LOG_DEBUG, ">>> [ Game_init ] - Game initialization [ done ]");
}

///
///
///
void Game_redraw(Game *game) {
    //
    // Scoreboard
    //
    Rectangle sb_rect = SB_redraw(&game->scoreboard);

    //
    // Table
    //
    Rectangle table_rect = Table_redraw(game, &sb_rect);

    //
    // Player rackets
    //
    Player_racket_redraw(&game->player1);
    Player_racket_redraw(&game->player2);

    //
    // Ball
    //
    Ball *ball = &game->ball;
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
        // Save the `table_rect` before toggling fullscreen
        game->table_rect_before_screen_changed = game->table_rect;

        //
        toggle_fullscreen(game);
        TraceLog(LOG_DEBUG,
                 ">>> [ Game_logic ] - Toggle fullscreen, screen_width: %d, "
                 "screen_height: %d",
                 GetScreenWidth(), GetScreenHeight());

        //
        // Update `game->table_rect`
        //
        Rectangle new_sb_rect = SB_recalculate_rect();
        game->table_rect = Table_recalculate_rect(&new_sb_rect);

        //
        // Sync racket position
        //
        Player_update_racket_after_screen_size_changed(
            &game->player1, &game->table_rect,
            &game->table_rect_before_screen_changed);
        Player_update_racket_after_screen_size_changed(
            &game->player2, &game->table_rect,
            &game->table_rect_before_screen_changed);
    }

    //
    // Press 'space' to start game
    //
    if (IsKeyPressed(KEY_SPACE) &&
        (game->state == GS_BEFORE_START || game->state == GS_PLAYER_WINS)) {
        game->state = GS_PLAYING;
        Ball_restart(&game->ball, &game->table_rect);
        Player_update_racket(&game->player1, &game->table_rect, RUT_RESET);
        Player_update_racket(&game->player2, &game->table_rect, RUT_RESET);
        Game_print_debug_info(game);
    }

    //
    // Game is playing, update all states
    //
    if (game->state == GS_PLAYING) {
        // Update ball
        Ball *ball = &game->ball;
        bool is_player1_win = false;
        bool is_player2_win = false;
        Ball_update(ball, &game->table_rect, &game->player1, &game->player2,
                    &is_player1_win, &is_player2_win);
        if (is_player1_win) {
            game->player1.score += 1;
            game->state = GS_PLAYER_WINS;
            game->is_player1_wins_last_round = true;
            PlaySound(game->you_win_sound_effect);
            return;
        } else if (is_player2_win) {
            game->player2.score += 1;
            game->state = GS_PLAYER_WINS;
            game->is_player1_wins_last_round = false;
            PlaySound(game->you_win_sound_effect);
            return;
        }

        // Update lighting tail
        Ball_update_lighting_tail(ball);

        /* TraceLog(LOG_DEBUG, */
        /*          ">>> [ Game_logic ] - ball center: { x: %.2f, y: %.2f, " */
        /*          "speed_x: %.2f, speed_Y: %.2f}", */
        /*          ball->center.x, ball->center.y, ball->speed_x,
         * ball->speed_y); */

        //
        // Update racket postion
        //
        if (IsKeyDown(PLAYER_2_UP_KEY)) {
            Player_update_racket(&game->player2, &game->table_rect,
                                 RUT_MOVE_UP);
        }
        if (IsKeyDown(PLAYER_2_DOWN_KEY)) {
            Player_update_racket(&game->player2, &game->table_rect,
                                 RUT_MOVE_DOWN);
        }
        if (IsKeyDown(PLAYER_1_UP_KEY)) {
            Player_update_racket(&game->player1, &game->table_rect,
                                 RUT_MOVE_UP);
        }
        if (IsKeyDown(PLAYER_1_DOWN_KEY)) {
            Player_update_racket(&game->player1, &game->table_rect,
                                 RUT_MOVE_DOWN);
        }
    }

    //
    // Player wins, update score
    //
    if (game->state == GS_PLAYING) {
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
        ClearBackground(GAME_UI_BACKGROUND_COLOR);

        //
        // Redraw the entire game
        //
        Game_redraw(game);

        EndDrawing();
    }

    TraceLog(LOG_DEBUG, ">>> [ Game_run ] - Exit the game loop");

    UnloadTexture(game->ball.alpha_mask);
    UnloadTexture(game->ball.lightning_ball);
    UnloadSound(game->you_win_sound_effect);
    UnloadSound(game->ball.enable_fireball_sound_effect);  // Unload sound data
    UnloadSound(game->ball.enable_lightning_ball_sound_effect);
    UnloadSound(game->ball.hit_racket_sound_effect);  // Unload sound data
    UnloadTexture(game->player1.default_racket.rect_texture);
    UnloadTexture(game->player2.default_racket.rect_texture);
    CloseAudioDevice();

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
    char player_1_str[300];
    Utils_get_player_string(&game->player1, player_1_str, sizeof(player_1_str));

    //
    // Player2
    //
    char player_2_str[300];
    Utils_get_player_string(&game->player2, player_2_str, sizeof(player_2_str));

    //
    // Ball
    //
    char ball_str[1024];
    char ball_color_str[10] = {0};
    char fireball_color_str[10] = {0};
    Utils_get_color_string(BALL_UI_BALL_COLOR, ball_color_str,
                           sizeof(ball_color_str));
    Utils_get_color_string(BALL_UI_FIREBALL_COLOR, fireball_color_str,
                           sizeof(fireball_color_str));
    snprintf(ball_str, sizeof(ball_str),
             "\tball: {\n\t\tcenter: { x: %.2f, y: %.2f }\n\t\tradius: "
             "%.2f\n\t\tcolor: 0x%s\n\t\tfireball color: 0x%s\n\t\tvelocity_x: "
             "%.2f\n\t\tvelocity_y: %.2f\n\t\thits_before_increase_velocity: "
             "%d\n\t\tvelocities_increase_to_enable_fireball: "
             "%d\n\t\tvelocity_acceleration: "
             "%d\n\t\tlighting_tail_particle_count: "
             "%d\n\t\tlighting_tail_particle_init_alpha: "
             "%.2f\n\t\tlighting_tail_particle_size: %.2f\n\t}",
             game->ball.center.x, game->ball.center.y, game->ball.radius,
             ball_color_str, fireball_color_str, BALL_UI_BALL_VELOCITY_X,
             BALL_UI_BALL_VELOCITY_Y, BALL_UI_HITS_BEFORE_INCREASE_VELOCITY,
             BALL_UI_VELOCITIES_INCREASE_TO_ENABLE_FIREBALL,
             BALL_UI_VELOCITY_ACCELERATION,
             BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT,
             BALL_UI_LIGHTING_TAIL_PRATICLE_INIT_ALPHA,
             BALL_UI_LIGHTING_TAIL_PRATICLE_SIZE);

    //
    // Debug info
    //
    snprintf(debug_info, sizeof(debug_info), "\n{\n\tstate: %s\n%s\n%s\n%s\n}",
             state_str, player_1_str, player_2_str, ball_str);

    TraceLog(LOG_DEBUG, ">>> [ Game_Print_debug_info ] - %s", debug_info);
}
