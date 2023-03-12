#ifndef __BALL_H__
#define __BALL_H__

#include <raylib.h>

#include "data_types.h"

#define BALL_LIGHTING_TAIL_PARTICLE_COUNT 50


///
/// Particle structure with basic data
///
typedef struct {
    Vector2 position;
    Color color;
    float alpha;
    float size;
    bool active;  // NOTE: Use it to activate/deactive particle
} BallTailParticle;

///
/// The lighting tail that follows by the moving ball
///
typedef struct {
    BallTailParticle particles[BALL_LIGHTING_TAIL_PARTICLE_COUNT];
    float particle_init_alpha;
    float particle_size;
} BallLightingTail;

///
///
///
typedef struct {
    Vector2 center;
    float radius;
    Color color;
    float speed_x;
    float speed_y;
    Texture2D alpha_mask;
    BallLightingTail lighting_tail;
} Ball;

///
///
///
void Ball_redraw(const Ball *ball);

///
///
///
void Ball_restart(Ball *ball, Rectangle *table_rect);

///
///
///
void Ball_update_ball(Ball *ball, Rectangle *table_rect);

///
///
///
void Ball_update_lighting_tail(Ball *ball);

#endif
