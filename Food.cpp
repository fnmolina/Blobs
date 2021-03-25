
#include "Food.h"
#include <iostream>
#include "Random.h"


Food::Food(int Xsize, int Ysize) {
	position = Point(random(Xsize), random(Ysize));
	state = NOT_EATEN;
}


