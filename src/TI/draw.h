#ifndef DRAW_H
#define DRAW_H

#include <math.h>
#include <graph.h>


#include "../graph.h"
#include "trigo.h"
#include "point.h"

typedef struct
{
    point v_point[3];
    point centre;
    int i_base;
    int i_height;
} Triangle;

/**
 @struct An arrow 
 @param Width of the full base of the arrowhead in pixels
 @param The angle at the arrow tip between the two sides of the arrowhead in radian
 @param Flag indicating whether or not the arrowhead should be filled (1) or not (0)
*/
typedef struct t_arrow
{
    int nWidth;
    float fTheta;
    char bFill;
} arrow;

void IntArrowTo(int FromX, int FromY, int ToX, int ToY, arrow *pA);
void PtArrowTo(point pFrom, point pTo, arrow *pArrow);
void arrow_draw(point point1, point point2, point point3);
void line_draw(point pointSource, point pointDest);
void graph_draw(const graph *p_graph);

#endif
