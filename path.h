#ifndef PATH_H
#define PATH_H

#include "summit.h"

/**
	@struct A data structure prepresenting a path between to summit
	@param the source summit
	@param the destination summit
	@param the weight of the summit
*/
typedef struct{
	summit *src;
	summit *dest;
	int i_weight;
}path;

#endif
