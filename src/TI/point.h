#ifndef POINT_H
#define POINT_H

typedef struct t_point
{
 int x;
 int y;
} point;

/**
 @brief Set a point from two integers
 @param value on the X axis
 @param value on the Y axis
 @return the point set from parameters
*/
point set_coord(int x, int y);

#endif
