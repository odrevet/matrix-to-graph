#ifndef DRAW_H
#define DRAW_H

#include <math.h>

#include <graph.h>
#include <sprites.h>

#include "../graph.h"
#include "../point.h"
#include "trigo.h"

/**
 @struct An arrow 
 @param Width of the full base of the arrowhead in pixels
 @param The angle at the arrow tip between the two sides of the arrowhead in radian
*/
typedef struct t_arrow
{
    int width;
    float theta;
} arrow;

void draw_arrow(point o_point_from, point o_point_to);
void line_draw(point pointSource, point pointDest);
void draw_graph(const graph *p_graph);
void draw_edge_weight(edge *v_edge, int i_nb_edge);
#endif
