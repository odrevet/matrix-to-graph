#include "trigo.h"

float get_angle(const node *UnSommetA, const node *UnSommetB)
{
    float angle;
    angle = atan2(UnSommetA->coord.i_y - UnSommetB->coord.i_y, UnSommetA->coord.i_x - UnSommetB->coord.i_x);
    return angle;
}

float degree_to_radian(float angle)
{
    angle = (PI * angle) / 180;
    return angle;
}

float radian_to_degree(float angle)
{
    angle = angle * (180 / PI);
    return angle;
}

int rotate_x(float angle, point Unpoint, point pointCentral)
{
    return (int)(cos(angle) * (Unpoint.i_x - pointCentral.i_x) - sin(angle) * (Unpoint.i_y - pointCentral.i_y) + pointCentral.i_x);
}

int rotate_y(float angle, point Unpoint, point pointCentral)
{
    return (int)(sin(angle) * (Unpoint.i_x - pointCentral.i_x) + cos(angle) * (Unpoint.i_y - pointCentral.i_y) + pointCentral.i_y);
}

point rotate(float angle, point Unpoint, point pointCentral)
{
    point pointTourne;
    pointTourne.i_x = rotate_x(angle, Unpoint, pointCentral);
    pointTourne.i_y = rotate_y(angle, Unpoint, pointCentral);
    return pointTourne;
}

point ortho_projection(point Unpoint, int iDecalage, float fAngle)
{
    point pointChasles;
    pointChasles.i_x = (Unpoint.i_x + iDecalage * cos(fAngle));
    pointChasles.i_y = (Unpoint.i_y + iDecalage * sin(fAngle));
    return pointChasles;
}
