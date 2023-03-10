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
} Ball;

///
///
///
void Ball_redraw(const Ball *ball);

///
///
///
void Ball_restart(Ball *ball, Rectangle *table_rect);

#endif
