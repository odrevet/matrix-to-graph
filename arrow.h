/**
	@file arrow.h
	@brief display and arrow
*/

#ifndef ARROW_H
#define ARROW_H

#include <tigcclib.h>
#include <math.h>

#include "point.h"
#include "display.h"

typedef struct{
	point v_point[3];
	point centre;
	int i_base;
	int i_height;
}Triangle;


/**
	@struct An arrow 
	@param Width of the full base of the arrowhead in pixels
	@param The angle at the arrow tip between the two sides of the arrowhead in radian
	@param Flag indicating whether or not the arrowhead should be filled (1) or not (0)
*/
typedef struct t_arrow {
	int nWidth;
	float fTheta;
	char bFill;
} arrow;

void IntArrowTo(int FromX, int FromY, int ToX, int ToY, arrow *pA);
void PtArrowTo(point pFrom, point pTo, arrow *pArrow);

#endif
