#ifndef __FOOD_H
#define __FOOD_H

#include "Point.h"

#define EATEN 0
#define NOT_EATEN 1

class Food {

public:
	Point position;
	int state;

	//Constructor de Food.
	Food(int Xsize = 1, int Ysize = 1);

};


#endif //__FOOD_H
