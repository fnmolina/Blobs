
#include "Food.h"
#include <iostream>


Food::Food(int Xsize, int Ysize) {
	position = Point(random(SCREEN_W), random(SCREEN_H));
	state = NOT_EATEN;
}


