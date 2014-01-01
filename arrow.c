#include "arrow.h"


// ArrowTo()
//
void IntArrowTo(int FromX, int FromY, int ToX, int ToY, arrow *pA) {

	point ptFrom = {FromX, FromY};
	point ptTo = {ToX, ToY};
	PtArrowTo(ptFrom, ptTo, pA);
}

// ArrowTo()
//
void PtArrowTo(point pFrom, point pTo, arrow *pA) {

	point pBase;
	point aptPoly[3];
	float vecLine[2];
	float vecLeft[2];
	float fLength;
	float th;
	float ta;

	// set to point
	aptPoly[0].i_x = pTo.i_x;
	aptPoly[0].i_y = pTo.i_y;

	// build the line vector
	vecLine[0] = (float) aptPoly[0].i_x - pFrom.i_x;
	vecLine[1] = (float) aptPoly[0].i_y - pFrom.i_y;

	// build the arrow base vector - normal to the line
	vecLeft[0] = - vecLine[1];
	vecLeft[1] = vecLine[0];

	// setup length parameters
	fLength = (float) sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
	th = pA->nWidth / (2.0f * fLength);
	ta = pA->nWidth / (2.0f * (tan(pA->fTheta) / 2.0f) * fLength);
	
	// find the base of the arrow
	pBase.i_x = (int) (aptPoly[0].i_x + -ta * vecLine[0]);
	pBase.i_y = (int) (aptPoly[0].i_y + -ta * vecLine[1]);

	// build the points on the sides of the arrow
	aptPoly[1].i_x = (int) (pBase.i_x + th * vecLeft[0]);
	aptPoly[1].i_y = (int) (pBase.i_y + th * vecLeft[1]);
	aptPoly[2].i_x = (int) (pBase.i_x + -th * vecLeft[0]);
	aptPoly[2].i_y = (int) (pBase.i_y + -th * vecLeft[1]);

		line_draw(pFrom, pBase);
		line_draw(pFrom, aptPoly[1]);
		line_draw(pFrom, aptPoly[0]);
		line_draw(pFrom, aptPoly[2]);
	
}

