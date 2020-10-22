#include "trigo.h"

float get_angle(const node *p_node_a, const node *p_node_b)
{
    return atan2(p_node_a->coord.y - p_node_b->coord.y, p_node_a->coord.x - p_node_b->coord.x);
}

int rotate_x(float angle, point o_point, point center)
{
    return (int)(cos(angle) * (o_point.x - center.x) - sin(angle) * (o_point.y - center.y) + center.x);
}

int rotate_y(float angle, point o_point, point center)
{
    return (int)(sin(angle) * (o_point.x - center.x) + cos(angle) * (o_point.y - center.y) + center.y);
}

point rotate(float angle, point o_point, point center)
{
    point point_res = {.x = rotate_x(angle, o_point, center),
                       .y = rotate_y(angle, o_point, center)};
    return point_res;
}

point ortho_projection(point o_point, int iShift, float fAngle)
{
    point point_res = {.x = o_point.x + iShift * cos(fAngle),
                       .y = o_point.y + iShift * sin(fAngle)};
    return point_res;
}
