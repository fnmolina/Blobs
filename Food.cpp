#include "Food.h"
#include <iostream>

//Necesitaria un define de screen_w o que me pasen el valor maximo que puede tomar.
#define SCREEN_W 2
#define SCREEN_H 3

Food::Food() {
	position = Point(rand() % SCREEN_W, rand() % SCREEN_H);
	state = NOT_EATEN;
}

//Sinceramente no se si esto de devolver un puntero se puede
Food* Food::create(void) {
	Food* f;
	f = &Food();
	return f;
}

//OPCION 2 DE createFood
/*void Food::createFood (void){
	x = rand() % SCREEN_W;
	y = rand() % SCREEN_H;
	estado = NOT_EATEN;
}*/

//No se si esto deberia ser con una referencia mas q con un puntero, pero no termino de entender el concepto.
void Food::destroy(Food* f){
	f->estado = EATEN;
	f = NULL;
	return;
}
