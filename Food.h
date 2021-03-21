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
	Food();

	//Esta funcion se encarga de crear Food y devolver un puntero a lo creado.
	Food* create();
	//Esta funcion se encarga de eliminar Food, cambiandole el estado y poniendole puntero null.
	void destroy(Food* f);
};

#endif //__FOOD_H