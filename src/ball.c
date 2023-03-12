#include "ball.h"

#include <raylib.h>
#include <stdlib.h>

///
///
///
void Ball_redraw(const Ball *ball) {
    if (ball == NULL) return;

    /* TraceLog(LOG_DEBUG, */
    /*          ">>> [ Ball_redraw ] - ball.center: { x: %.2f, y: %.2f}", */
    /*          ball->center.x, ball->center.y); */

    if (ball == NULL || ball->center.x == -1 || ball->center.y == -1) return;

    //
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
    //
    BeginBlendMode(BLEND_ADDITIVE);

    //
    // Draw lighting tail
    //
    const BallTailParticle *particles = ball->lighting_tail.particles;

    for (usize i = 0; i < BALL_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
        if (ball->lighting_tail.particles[i].active)
            // TraceLog(LOG_DEBUG,
            //          ">>> [ Ball_redraw ] - draw lighting ball particle, "
            //          "index: {%u}",
            //          i);
            DrawTexturePro(
                ball->alpha_mask,
                (Rectangle){0.0f, 0.0f, (float)ball->alpha_mask.width,
                            (float)ball->alpha_mask.height},
                (Rectangle){particles[i].position.x, particles[i].position.y,
                            ball->alpha_mask.width * particles[i].size,
                            ball->alpha_mask.height * particles[i].size},
                (Vector2){
                    (float)(ball->alpha_mask.width * particles[i].size / 2.0f),
                    (float)(ball->alpha_mask.height * particles[i].size /
                            2.0f)},
                0.0f, Fade(particles[i].color, particles[i].alpha));
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

    BallTailParticle *particles = ball->lighting_tail.particles;

    for (int i = 0; i < BALL_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
        particles[i].position = (Vector2){0, 0};
        particles[i].color = ball->color;

        // Init `alpha` value, it affects how light the particle at the
        // beginning
        particles[i].alpha = ball->lighting_tail.particle_init_alpha;

        // It affects how big the particle will be: how many percentage of the
        // ball size: 0.0 ~ 1.0 (0 ~ 100%)
        particles[i].size = ball->lighting_tail.particle_size;
        particles[i].active = false;
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
    BallTailParticle *particles = ball->lighting_tail.particles;

    for (int i = 0; i < BALL_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
        if (!particles[i].active) {
            particles[i].active = true;
            particles[i].alpha = ball->lighting_tail.particle_init_alpha;
            particles[i].position = ball->center;
            i = BALL_LIGHTING_TAIL_PARTICLE_COUNT;
        }
    }

    for (int i = 0; i < BALL_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
        if (particles[i].active) {
            // particles[i].position.y += gravity / 2;
            particles[i].alpha -= 0.05f;

            if (particles[i].alpha <= 0.0f) particles[i].active = false;
        }
    }
}
