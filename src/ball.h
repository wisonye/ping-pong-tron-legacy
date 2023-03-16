#ifndef __BALL_H__
#define __BALL_H__

#include <raylib.h>

#include "config.h"
#include "data_types.h"
#include "player.h"

///
/// Particle structure with basic data
///
typedef struct {
    Vector2 position;
    // Color color;
    float alpha;
    float size;
    bool active;  // NOTE: Use it to activate/deactive particle
} BallTailParticle;

///
/// The lighting tail that follows by the moving ball
///
typedef struct {
    BallTailParticle particles[BALL_UI_LIGHTING_TAIL_PARTICLE_COUNT];
} BallLightingTail;

///
///
///
typedef struct {
    Vector2 center;
    float velocity_x;
    float velocity_y;
    usize current_hits;
    usize current_velocities_increase;
    bool enabled_fireball;
    Texture2D alpha_mask;
    Sound enable_fireball_sound_effect;
    Sound hit_racket_sound_effect;
    BallLightingTail lighting_tail;
} Ball;

///
///
///
void Ball_redraw(const Ball *ball);

///
///
///
void Ball_restart(Ball *ball, const Rectangle *table_rect);

///
///
///
void Ball_update(Ball *ball, const Rectangle *table_rect, const Player *player1,
                 const Player *player2, bool *is_player1_win,
                 bool *is_player2_win);

///
///
///
void Ball_update_lighting_tail(Ball *ball);

#endif
