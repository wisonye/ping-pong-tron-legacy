#ifndef __BALL_H__
#define __BALL_H__

#include <raylib.h>

#include "data_types.h"

///
///
///
typedef struct Ball {
    Vector2 center;
    float radius;
    Color color;
    float speed_x;
    float speed_y;
    Texture2D alpha_mask;
} Ball;

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
