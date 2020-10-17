#ifndef TRIGO_H
#define TRIGO_H

#include <tigcclib.h>
#include <math.h>

#include "point.h"
#include "node.h"

/**
 @brief get the angle between two  node
 @param the first  node
 @param the second  node
 @return the angle
 @note angle is in degree
 @todo change the prototype of this function with only point instead of  node, to reduice dependancies
*/
float get_angle(const  node *UnSommetA, const  node *UnSommetB);

/**
 @brief convert degree to radian
 @param the angle in degree
 @return the angle in radian
*/
float degree_to_radian(float angle);

/**
 @brief convert radian to degree
 @param the angle in radian
 @return the angle in degree
*/
float radian_to_degree(float angle);

/**
 @brief rotate a point on x axis
 @param angle of rotation
 @param the point to rotate
 @param the cernter of the rotation
 @return the new location on X axis
*/
int rotate_x(float angle, point Unpoint, point pointCentral);

/**
 @brief
 @param
 @return
*/
int rotate_y(float angle, point Unpoint, point pointCentral);

/**
 @brief
 @param
 @return
*/
point rotate(float angle, point Unpoint, point pointCentral);

/**
 @brief
 @param
 @return
*/
point ortho_projection(point Unpoint, int iDecalage, float fAngle);

#endif
