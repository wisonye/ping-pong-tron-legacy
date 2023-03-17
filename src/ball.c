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

    if (ball->enabled_lightning_ball) {
        ball_and_lighting_tail_color = BALL_UI_LIGHTNING_BALL_COLOR;
    }

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
                   0.0f, ball_and_lighting_tail_color);

    EndBlendMode();

    //
    // Draw lightning ball with texture png version
    //
    // if (ball->enabled_lightning_ball) {
    //     BeginBlendMode(BLEND_ALPHA);

    //     DrawTexturePro(
    //         ball->lightning_ball,
    //         (Rectangle){0.0f, 0.0f, (float)ball->lightning_ball.width,
    //                     (float)ball->lightning_ball.height},
    //         (Rectangle){ball->center.x, ball->center.y, 2 * ball->radius,
    //                     2 * ball->radius},
    //         (Vector2){(float)(ball->radius), (float)(ball->radius)},
    //         ball->lightning_ball_rotation_angle,
    //         (Color){.r = 0xFF, .g = 0xFF, .b = 0xFF, .a = 0xFF});

    //     EndBlendMode();
    // }
}

///
/// Reset the ball and lighting tail
///
void Ball_restart(Ball *ball, const Rectangle *table_rect) {
    if (ball == NULL) return;

    ball->center = (Vector2){
        .x = table_rect->x + ((table_rect->width - ball->radius) / 2),
        .y = table_rect->y + ((table_rect->height - ball->radius) / 2),
    };

    ball->velocity_x = BALL_UI_BALL_VELOCITY_X;
    ball->velocity_y = BALL_UI_BALL_VELOCITY_Y;
    ball->current_hits = 0;
    ball->current_velocities_increase = 0;
    ball->enabled_fireball = false;
    ball->enabled_lightning_ball = false;

    BallTailParticle *particles = ball->lighting_tail.particles;

    for (int i = 0; i < BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
        particles[i].position = (Vector2){0, 0};
        // particles[i].color = ball->color;

        // Init `alpha` value, it affects how light the particle at the
        // beginning
        particles[i].alpha = BALL_UI_LIGHTING_TAIL_PRATICLE_INIT_ALPHA;

        // It affects how big the particle will be: how many percentage of the
        // ball size: 0.0 ~ 1.0 (0 ~ 100%)
        particles[i].size = BALL_UI_LIGHTING_TAIL_PRATICLE_SIZE;
        particles[i].active = false;
    }
}

///
///
///
void Ball_update(Ball *ball, const Rectangle *table_rect, const Player *player1,
                 const Player *player2, bool *is_player1_win,
                 bool *is_player2_win) {
    //
    // Next ball position
    //
    ball->center.x += GetFrameTime() * ball->velocity_x;
    ball->center.y += GetFrameTime() * ball->velocity_y;

    //
    // Ball bouncing in table
    //

    // If `ball` hit the top of `table_rect`
    if (ball->center.y - ball->radius <= table_rect->y) {
        ball->center.y = table_rect->y + ball->radius;
        ball->velocity_y *= -1;  // Flip the velocity_y direction
    }
    // If `ball` hit the bottom of `table_rect`
    else if (ball->center.y + ball->radius >=
             table_rect->y + table_rect->height) {
        ball->center.y = table_rect->y + table_rect->height - ball->radius;
        ball->velocity_y *= -1;  // Flip the velocity_y direction
    }

    //
    // Win or lose
    //

    // If `ball` hit the left of `table_rect`
    if (ball->center.x <= table_rect->x) {
        *is_player2_win = true;
        return;
    }
    // If `ball` hit the right of `table_rect`
    else if (ball->center.x >= table_rect->x + table_rect->width) {
        *is_player1_win = true;
        return;
    }

    //
    // Hit player's racket to increase the velocity
    //
    Vector2 ball_left_point =
        (Vector2){.x = ball->center.x - ball->radius, .y = ball->center.y};
    Vector2 ball_right_point =
        (Vector2){.x = ball->center.x + ball->radius, .y = ball->center.y};

    // If `ball` hit the left player's racket
    if (CheckCollisionPointRec(ball_left_point, player1->default_racket.rect)) {
        TraceLog(LOG_DEBUG, ">>> [ Ball_update ] - Hit player 1 racket");
        ball->center.x = player1->default_racket.rect.x +
                         player1->default_racket.rect.width + ball->radius;
        ball->velocity_x *= -1;  // Flip the velocity_x direction
        ball->current_hits += 1;
        PlaySound(ball->hit_racket_sound_effect);
    }
    // If `ball` hit the right player's racket
    else if (CheckCollisionPointRec(ball_right_point,
                                    player2->default_racket.rect)) {
        TraceLog(LOG_DEBUG, ">>> [ Ball_update ] - Hit player 2 racket");
        ball->center.x = player2->default_racket.rect.x - ball->radius;
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

        //
        // Enable lightning ball
        //
        if (!ball->enabled_lightning_ball &&
            ball->current_velocities_increase >=
                BALL_UI_VELOCITIES_INCREASE_TO_ENABLE_LIGHTNING_BALL) {
            ball->enabled_lightning_ball = true;
            PlaySound(ball->enable_lightning_ball_sound_effect);
            TraceLog(LOG_DEBUG, ">>> [ Ball_update ] - Enabled lightning ball");

            // Reduce ball radius
            ball->radius = BALL_UI_LIGHTING_BALL_RADIUS;

            // Reduce the tail particle size
            BallTailParticle *particles = ball->lighting_tail.particles;
            for (int i = 0; i < BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT; i++) {
                // It affects how big the particle will be: how many percentage
                // of the ball size: 0.0 ~ 1.0 (0 ~ 100%)
                particles[i].size =
                    BALL_UI_LIGHTING_TAIL_PRATICLE_SIZE_FOR_LIGHTNING_BALL;
            }
        }
    }

    //
    // Update lightning ball attriubtes
    //
    if (ball->enabled_lightning_ball) {
        ball->lightning_ball_rotation_angle += 32.0f;
        if (ball->lightning_ball_rotation_angle > 360) {
            ball->lightning_ball_rotation_angle = 0;
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
            particles[i].alpha = BALL_UI_LIGHTING_TAIL_PRATICLE_INIT_ALPHA;
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
