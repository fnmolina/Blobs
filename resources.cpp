
#include "resources.h"
#include <iostream>

#define DEC_PRECISION 1000


//DEVUELVE UN NÚMERO ALEATORIO FLOAT ENTRE 0 Y "max".
float random(int max) {
	float units, dec;
	units = rand() % max;	//Se calcula aleatoriamente las unidades
	dec = rand() % DEC_PRECISION;	//Se calculan los puntos decimales
	return ((float)units + (float)(dec / DEC_PRECISION));	//Se suman ambos y se devuelve el numero
}