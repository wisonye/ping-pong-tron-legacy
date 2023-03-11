#include "ball.h"

#include <raylib.h>
#include <stdlib.h>

#define PARTICLE_COUNT 50

/// Init `alpha` value, it affects how light the particle at the beginning
#define LIGHT_TRAIL_PRATICLE_INIT_ALPHA 0.8f

/// It affects how big the particle will be: how many percentage of the ball
/// size: 0.0 ~ 1.0 (0 ~ 100%)
#define LIGHT_TRAIL_PRATICLE_SIZE 0.6f

///
/// The lighting tail that follows by the moving ball
///
BallTailParticle lighting_trail[PARTICLE_COUNT] = {0};

///
///
///
void Ball_redraw(const Ball *ball) {
    if (ball == NULL) return;

    /* TraceLog(LOG_DEBUG, */
    /*          ">>> [ Ball_redraw ] - ball.center: { x: %.2f, y: %.2f}", */
    /*          ball->center.x, ball->center.y); */

    if (ball == NULL || ball->center.x == -1 || ball->center.y == -1) return;

    // // Color blending modes (pre-defined)
    // typedef enum {
    // BLEND_ALPHA = 0,         // Blend textures considering alpha (default)
    // BLEND_ADDITIVE,          // Blend textures adding colors
    // BLEND_MULTIPLIED,        // Blend textures multiplying colors
    // BLEND_ADD_COLORS,        // Blend textures adding colors (alternative)
    // BLEND_SUBTRACT_COLORS,   // Blend textures subtracting colors
    // (alternative) BLEND_ALPHA_PREMULTIPLY, // Blend premultiplied textures
    // considering alpha BLEND_CUSTOM             // Blend textures using custom
    // src/dst factors (use rlSetBlendMode()) } BlendMode;
    //
    //
    // Above is the supported `blend mode` which affects how blending works,
    // `BLEND_ADDTIVE` is the only effect I wanted.
    BeginBlendMode(BLEND_ADDITIVE);

    //
    // Draw lighting tail
    //
    for (usize i = 0; i < PARTICLE_COUNT; i++) {
        if (lighting_trail[i].active)
            // TraceLog(LOG_DEBUG,
            //          ">>> [ Ball_redraw ] - draw lighting ball particle, "
            //          "index: {%u}",
            //          i);
            DrawTexturePro(
                ball->alpha_mask,
                (Rectangle){0.0f, 0.0f, (float)ball->alpha_mask.width,
                            (float)ball->alpha_mask.height},
                (Rectangle){lighting_trail[i].position.x,
                            lighting_trail[i].position.y,
                            ball->alpha_mask.width * lighting_trail[i].size,
                            ball->alpha_mask.height * lighting_trail[i].size},
                (Vector2){(float)(ball->alpha_mask.width *
                                  lighting_trail[i].size / 2.0f),
                          (float)(ball->alpha_mask.height *
                                  lighting_trail[i].size / 2.0f)},
                0.0f, Fade(lighting_trail[i].color, lighting_trail[i].alpha));
    }
    //
    // Draw solid circle
    //
    // DrawCircleV(ball->center, ball->radius, ball->color);

    //
    // Draw ball with alpha mask
    //
    DrawTexturePro(ball->alpha_mask,
                   (Rectangle){0.0f, 0.0f, (float)ball->alpha_mask.width,
                               (float)ball->alpha_mask.height},
                   (Rectangle){ball->center.x, ball->center.y,
                               ball->alpha_mask.width, ball->alpha_mask.height},
                   (Vector2){(float)(ball->alpha_mask.width / 2.0f),
                             (float)(ball->alpha_mask.height / 2.0f)},
                   0.0f, ball->color);
    EndBlendMode();
}

///
/// Reset the ball and lighting tail
///
void Ball_restart(Ball *ball, Rectangle *table_rect) {
    if (ball == NULL) return;

    ball->center = (Vector2){
        .x = table_rect->x + ((table_rect->width - ball->radius) / 2),
        .y = table_rect->y + ((table_rect->height - ball->radius) / 2),
    };

    for (int i = 0; i < PARTICLE_COUNT; i++) {
        lighting_trail[i].position = (Vector2){0, 0};
        lighting_trail[i].color = ball->color;

        // Init `alpha` value, it affects how light the particle at the
        // beginning
        lighting_trail[i].alpha = LIGHT_TRAIL_PRATICLE_INIT_ALPHA;

        // It affects how big the particle will be: how many percentage of the
        // ball size: 0.0 ~ 1.0 (0 ~ 100%)
        lighting_trail[i].size = LIGHT_TRAIL_PRATICLE_SIZE;
        lighting_trail[i].active = false;
    }
}

///
///
///
void Ball_update_ball(Ball *ball, Rectangle *table_rect) {
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
}

///
///
///
void Ball_update_lighting_tail(Ball *ball) {
    //
    // Activate one particle every frame and Update active particles
    // NOTE: Particles initial position should be mouse position when
    // activated NOTE: Particles fall down with gravity and rotation... and
    // disappear after 2 seconds (alpha = 0) NOTE: When a particle
    // disappears, active = false and it can be reused.
    //
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        if (!lighting_trail[i].active) {
            lighting_trail[i].active = true;
            lighting_trail[i].alpha = LIGHT_TRAIL_PRATICLE_INIT_ALPHA;
            lighting_trail[i].position = ball->center;
            i = PARTICLE_COUNT;
        }
    }

    for (int i = 0; i < PARTICLE_COUNT; i++) {
        if (lighting_trail[i].active) {
            // lighting_trail[i].position.y += gravity / 2;
            lighting_trail[i].alpha -= 0.05f;

            if (lighting_trail[i].alpha <= 0.0f)
                lighting_trail[i].active = false;
        }
    }
}
