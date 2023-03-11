#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "data_types.h"

#define PARTICLE_COUNT 10

//
// Color theme
//
#define TRON_DARK \
    (Color) { .r = 0x23, .g = 0x21, .b = 0x1B, .a = 0xFF }
#define TRON_LIGHT_BLUE \
    (Color) { .r = 0xAC, .g = 0xE6, .b = 0xFE, .a = 0xFF }
#define TRON_BLUE \
    (Color) { .r = 0x6F, .g = 0xC3, .b = 0xDF, .a = 0xFF }
#define TRON_YELLOW \
    (Color) { .r = 0xFF, .g = 0xE6, .b = 0x4D, .a = 0xFF }
#define TRON_ORANGE \
    (Color) { .r = 0xFF, .g = 0x9F, .b = 0x1C, .a = 0xFF }
#define TRON_RED \
    (Color) { .r = 0xF4, .g = 0x47, .b = 0x47, .a = 0xFF }
#define GAME_UI_BALL_COLOR TRON_LIGHT_BLUE
// #define GAME_UI_BALL_COLOR TRON_ORANGE
// #define GAME_UI_BALL_COLOR TRON_YELLOW
#define GAME_UI_BALL_RADIUS 20.0f

typedef struct Ball {
    Vector2 center;
    float radius;
    Color color;
    float speed_x;
    float speed_y;
    float alpha;
} Ball;

#define MAX_PARTICLES 50

// Particle structure with basic data
typedef struct {
    Vector2 position;
    Color color;
    float alpha;
    float size;
    float rotation;
    bool active;  // NOTE: Use it to activate/deactive particle
} Particle;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screen_width = 800;
    const int screen_height = 450;

    InitWindow(screen_width, screen_height,
               "raylib [textures] example - particles blending");

    Ball ball = (Ball){
        .center = (Vector2){.x = (screen_width - GAME_UI_BALL_RADIUS * 2) / 2,
                            .y = (screen_height - GAME_UI_BALL_RADIUS * 2) / 2},
        .radius = GAME_UI_BALL_RADIUS,
        .color = GAME_UI_BALL_COLOR,
        .alpha = 1.0,
    };

    // Particles pool, reuse them!
    Particle mouseTail[MAX_PARTICLES] = {0};

    // Initialize particles
    for (int i = 0; i < MAX_PARTICLES; i++) {
        mouseTail[i].position = (Vector2){0, 0};
        mouseTail[i].color = ball.color;
            // (Color){.r = 0x6F, .g = 0xC3, .b = 0xDF, .a = 0xFF};
        mouseTail[i].alpha = 0.5f;
        mouseTail[i].size = 0.6f;
        mouseTail[i].rotation = (float)GetRandomValue(0, 360);
        mouseTail[i].active = false;
    }

    Image particle_image = GenImageGradientRadial(
        ball.radius * 2, ball.radius * 2, 0.5f, WHITE, BLACK);
    Texture2D particle_texture = LoadTextureFromImage(particle_image);
    Texture2D ball_texture = LoadTextureFromImage(particle_image);
    UnloadImage(particle_image);

    int init_blending = BLEND_ALPHA;
    // int init_blending  = BLEND_MULTIPLIED;
    // int init_blending  = BLEND_ADD_COLORS;
    // int init_blending  = BLEND_SUBTRACT_COLORS;
    // int init_blending  = BLEND_ALPHA_PREMULTIPLY;
    int blending = init_blending;

    HideCursor();

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())  // Detect window close button or ESC key
    {
        Vector2 mouse_pos = GetMousePosition();

        // Update
        //----------------------------------------------------------------------------------

        // Activate one particle every frame and Update active particles
        // NOTE: Particles initial position should be mouse position when
        // activated NOTE: Particles fall down with gravity and rotation... and
        // disappear after 2 seconds (alpha = 0) NOTE: When a particle
        // disappears, active = false and it can be reused.
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (!mouseTail[i].active) {
                mouseTail[i].active = true;
                mouseTail[i].alpha = 0.8f;
                mouseTail[i].position = mouse_pos;
                i = MAX_PARTICLES;
            }
        }

        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (mouseTail[i].active) {
                // mouseTail[i].position.y += gravity / 2;
                mouseTail[i].alpha -= 0.05f;

                if (mouseTail[i].alpha <= 0.0f) mouseTail[i].active = false;

                // mouseTail[i].rotation += 2.0f;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            if (blending == init_blending)
                blending = BLEND_ADDITIVE;
            else
                blending = init_blending;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(TRON_DARK);

        BeginBlendMode(blending);

        // Draw active particles
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (mouseTail[i].active)
                DrawTexturePro(
                    particle_texture,
                    (Rectangle){0.0f, 0.0f, (float)particle_texture.width,
                                (float)particle_texture.height},
                    (Rectangle){mouseTail[i].position.x,
                                mouseTail[i].position.y,
                                particle_texture.width * mouseTail[i].size,
                                particle_texture.height * mouseTail[i].size},
                    (Vector2){(float)(particle_texture.width *
                                      mouseTail[i].size / 2.0f),
                              (float)(particle_texture.height *
                                      mouseTail[i].size / 2.0f)},
                    0.0f, Fade(mouseTail[i].color, mouseTail[i].alpha));
        }

        DrawTexturePro(ball_texture,
                       (Rectangle){0.0f, 0.0f, (float)ball_texture.width,
                           (float)ball_texture.height},
                       (Rectangle){mouse_pos.x, mouse_pos.y, ball_texture.width,
                           ball_texture.height},
                       (Vector2){(float)(ball_texture.width / 2.0f),
                           (float)(ball_texture.height / 2.0f)},
                       0.0f, ball.color);

        DrawText("PRESS SPACE to CHANGE BLENDING MODE", 180, 20, 20, BLACK);

        if (blending == BLEND_ALPHA)
            DrawText("ALPHA BLENDING", 290, screen_height - 40, 20, BLACK);
        else
            DrawText("ADDITIVE BLENDING", 280, screen_height - 40, 20,
                     RAYWHITE);

        EndBlendMode();


        // DrawCircleV(GetMousePosition(), 20.0f, (Color) { .r = 0xAC, .g =
        // 0xE6, .b = 0xFE, .a = 0xFF });
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(particle_texture);

    CloseWindow();  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
