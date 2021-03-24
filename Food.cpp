#include "Food.h"
#include <iostream>

Food::Food() {
	position = Point(random(SCREEN_W), random(SCREEN_H));
	state = NOT_EATEN;
}

//Sinceramente no se si esto de devolver un puntero se puede
/*
Food* Food::create(void) {
	Food* f;
	f = &Food();
	return f;
}*/

//OPCION 2 DE createFood
/*void Food::createFood (void){
	x = rand() % SCREEN_W;
	y = rand() % SCREEN_H;
	estado = NOT_EATEN;
}*/

//No se si esto deberia ser con una referencia mas q con un puntero, pero no termino de entender el concepto.

//void food::destroy(food* f){
//	f->state = eaten;
//	f = null;
//	return;
//}
