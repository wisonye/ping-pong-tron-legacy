#include "ball.h"

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

    DrawCircleV(ball->center, ball->radius, ball->color);
}

///
///
///
void Ball_restart(Ball *ball, Rectangle *table_rect) {
    if (ball == NULL) return;

    ball->center = (Vector2){
        .x = table_rect->x + ((table_rect->width - ball->radius) / 2),
        .y = table_rect->y + ((table_rect->height - ball->radius) / 2),
    };
}
