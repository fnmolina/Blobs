#include <iostream>
#include "Blob.h"

//Otra vez, necesitaria o que me manden el max de x e y como parametro o que haya un define
#define SCREEN_W 1
#define SCREEN_H 2

Blob::Blob() {
	position = (rand()%SCREEN_W, rand()%SCREEN_H);
	blobMovement = rand()%360; //direccion de movimiento
	switch (etaryGroup){
		case BABY_BLOB:
			etaryGroup = GROWN_BLOB;
			break;
		case GROWN_BLOB:
			etaryGroup = GOOD_OLD_BLOB;
			break;
		case GOOD_OLD_BLOB:
			//No tengo idea que deberia pasar aca, pero no deberia ser lo mismo que el default. No se si matarlo o que.
			break;
		default:
			etaryGroup = BABY_BLOB;
			break;
	}
	foodCount = 0;
	blobDeathProb = rand()%1; //Valor random entre 0 y 1?????????
	maxSpeed = 0;
}

//void adjustMovement();
//void move();
void Blob::feed(void) {
	++foodCount;
	switch (etaryGroup) {
	case BABY_BLOB:
		if (foodCount == 3){
			grow();
		}
		break;
	case GROWN_BLOB:
		if (foodCount == 4) {
			grow();
		}
		break;
	case GOOD_OLD_BLOB:
		if (foodCount == 5) {
			grow();
		}
		break;
	}
}
void Blob::grow() {
	switch (etaryGroup) {
	case BABY_BLOB:
		etaryGroup = GROWN_BLOB;
		break;
	case GROWN_BLOB:
		etaryGroup = GOOD_OLD_BLOB;
		break;
	case GOOD_OLD_BLOB:
		//no se q pasaria aca, lo matamos?
		break;
	}
}
//void destroy(void);
