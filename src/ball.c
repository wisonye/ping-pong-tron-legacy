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

    Color ball_and_lighting_tail_color =
        ball->enabled_fireball ? BALL_UI_FIREBALL_COLOR : BALL_UI_BALL_COLOR;

    for (usize i = 0; i < BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
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
                0.0f,

                Fade(ball_and_lighting_tail_color, particles[i].alpha));
    }
    //
    // Draw solid circle
    //
    // DrawCircleV(ball->center, BALL_UI_BALL_RADIUS, ball->color);

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
                   0.0f, ball_and_lighting_tail_color);
    EndBlendMode();
}

///
/// Reset the ball and lighting tail
///
void Ball_restart(Ball *ball, Rectangle *table_rect) {
    if (ball == NULL) return;

    ball->center = (Vector2){
        .x = table_rect->x + ((table_rect->width - BALL_UI_BALL_RADIUS) / 2),
        .y = table_rect->y + ((table_rect->height - BALL_UI_BALL_RADIUS) / 2),
    };
    ball->current_hits = 0;
    ball->current_velocities_increase = 0;
    ball->enabled_fireball = false;

    BallTailParticle *particles = ball->lighting_tail.particles;

    for (int i = 0; i < BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
        particles[i].position = (Vector2){0, 0};
        // particles[i].color = ball->color;

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
void Ball_update(Ball *ball, Rectangle *table_rect) {
    //
    // Next ball position
    //
    ball->center.x += GetFrameTime() * ball->velocity_x;
    ball->center.y += GetFrameTime() * ball->velocity_y;

    //
    // Ball bouncing in table
    //

    // If `ball` hit the top of `table_rect`
    if (ball->center.y - BALL_UI_BALL_RADIUS <= table_rect->y) {
        ball->center.y = table_rect->y + BALL_UI_BALL_RADIUS;
        ball->velocity_y *= -1;  // Flip the velocity_y direction
    }
    // If `ball` hit the bottom of `table_rect`
    else if (ball->center.y + BALL_UI_BALL_RADIUS >=
             table_rect->y + table_rect->height) {
        ball->center.y =
            table_rect->y + table_rect->height - BALL_UI_BALL_RADIUS;
        ball->velocity_y *= -1;  // Flip the velocity_y direction
    }

    //
    // Win or lose
    //

    // If `ball` hit the left of `table_rect`
    // if (ball->center.x - BALL_UI_BALL_RADIUS <= table_rect->x) {
    //     ball->center.x = table_rect->x + BALL_UI_BALL_RADIUS;
    //     ball->velocity_x *= -1;  // Flip the velocity_x direction
    // }
    // // If `ball` hit the right of `table_rect`
    // else if (ball->center.x + BALL_UI_BALL_RADIUS >=
    //          table_rect->x + table_rect->width) {
    //     ball->center.x = table_rect->x + table_rect->width -
    //     BALL_UI_BALL_RADIUS; ball->velocity_x *= -1;  // Flip the velocity_x
    //     direction
    // }

    //
    // Hit player's racket to increase the velocity
    //

    // If `ball` hit the left player's racket
    if (ball->center.x - BALL_UI_BALL_RADIUS <= table_rect->x) {
        ball->center.x = table_rect->x + BALL_UI_BALL_RADIUS;
        ball->velocity_x *= -1;  // Flip the velocity_x direction
        ball->current_hits += 1;
        PlaySound(ball->hit_racket_sound_effect);
    }
    // If `ball` hit the right player's racket
    else if (ball->center.x + BALL_UI_BALL_RADIUS >=
             table_rect->x + table_rect->width) {
        ball->center.x =
            table_rect->x + table_rect->width - BALL_UI_BALL_RADIUS;
        ball->velocity_x *= -1;  // Flip the velocity_x direction
        ball->current_hits += 1;
        PlaySound(ball->hit_racket_sound_effect);
    }

    if (ball->current_hits >= BALL_UI_HITS_BEFORE_INCREASE_VELOCITY) {
        // Increase `current_velocities_increase `
        ball->current_velocities_increase += 1;

        // Reset
        ball->current_hits = 0;

        // Increase speed
        ball->velocity_x =
            (ball->velocity_x > 0)
                ? ball->velocity_x + BALL_UI_VELOCITY_ACCELERATION
                : ball->velocity_x - BALL_UI_VELOCITY_ACCELERATION;
        ball->velocity_y =
            (ball->velocity_y > 0)
                ? ball->velocity_y + BALL_UI_VELOCITY_ACCELERATION
                : ball->velocity_y - BALL_UI_VELOCITY_ACCELERATION;

        TraceLog(LOG_DEBUG,
                 ">>> [ Ball_update ] - %u hits happens, increase velocity to "
                 "(x: %.2f, y: %.2f), "
                 "current_velocities_increase: %u",
                 BALL_UI_HITS_BEFORE_INCREASE_VELOCITY, ball->velocity_x,
                 ball->velocity_y, ball->current_velocities_increase);

        //
        // Enable fireball
        //
        if (!ball->enabled_fireball &&
            ball->current_velocities_increase >=
                BALL_UI_VELOCITIES_INCREASE_TO_ENABLE_FIREBALL) {
            ball->enabled_fireball = true;
            PlaySound(ball->enable_fireball_sound_effect);
            TraceLog(LOG_DEBUG, ">>> [ Ball_update ] - Enabled fireball");
        }
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
    ;
    for (int i = 0; i < BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
        if (!particles[i].active) {
            particles[i].active = true;
            particles[i].alpha = ball->lighting_tail.particle_init_alpha;
            particles[i].position = ball->center;
            i = BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT;
        }
    }

    for (int i = 0; i < BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
        if (particles[i].active) {
            // particles[i].position.y += gravity / 2;
            particles[i].alpha -= 0.05f;

            if (particles[i].alpha <= 0.0f) particles[i].active = false;
        }
    }
}
