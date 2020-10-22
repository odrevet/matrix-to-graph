#ifndef TRIGO_H
#define TRIGO_H

#include <math.h>

#include "../point.h"
#include "../node.h"

/**
 @brief get the angle between two  node
 @param the first  node
 @param the second  node
 @return the angle
 @note angle is in degree
 @todo change the prototype of this function with only point instead of  node, to reduice dependancies
*/
float get_angle(const  node *p_node_a, const  node *p_node_b);

/**
 @brief rotate a point on x axis
 @param angle of rotation
 @param the point to rotate
 @param the cernter of the rotation
 @return the new location on X axis
*/
int rotate_x(float angle, point o_point, point center);
int rotate_y(float angle, point o_point, point center);

point rotate(float angle, point o_point, point center);

point ortho_projection(point o_point, int iShift, float fAngle);

#endif
