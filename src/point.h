#ifndef POINT_H
#define POINT_H

#include <tigcclib.h>

typedef struct t_point
{
 int i_x;
 int i_y;
} point;

/**
 @brief Set a point from two integers
 @param value on the X axis
 @param value on the Y axis
 @return the point set from parameters
*/
point set_coord(int x, int y);

#endif
