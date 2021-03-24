#include <iostream>
#include "Blob.h"

#define MOVEMENT 1//No se si lo tendria q relacionar con la velocidad del muñequito

#define MAX_ANGLE	360

using namespace std;

/*
Blob::Blob() {
	position = (rand()%SCREEN_W, rand()%SCREEN_H);
	direction = rand()%360; //direccion de movimiento
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
	deathProb = random(1); //Valor random entre 0 y 1?????????
	speed = 0;
}*/

Blob::Blob(int mode, int speedMax, float speedProb, float deathProbBabyBlob) {

	position = {random(SCREEN_W), random(SCREEN_H)};
	direction = random(MAX_ANGLE); //direccion de movimiento
	etaryGroup = BABY_BLOB;
	foodCount = 0;
	deathProb = deathProbBabyBlob; 
	adjustSpeed(mode, speedMax, speedProb);
}

//Si la distancia entre el blob y la comida es menor o igual que SmellRadius entonces se dirige hacia la comida.
void Blob::adjustMovement (Point& food, double SmellRadius) {
	if (position.getDistance(food) <= SmellRadius){
		direction = position.getAngle(food);
	}
	return;
}

//Ajusta velocidad de blob segun modo de simulacion.
void Blob::adjustSpeed(int mode, int speedMax, float speedProb) {
	if (mode == 1) {
		speed = speedMax;
	}
	else {
		speed = random(speedMax);
	}
	speed *= speedProb;
}

//Cambia la posicion del blob.
void Blob::move (Point& food, double SmellRadius) {
	adjustMovement(food, SmellRadius);
	position.translate(MOVEMENT, direction);
	if (position.x > SCREEN_W){
		position.x = 0;
	}
	else if (position.x < 0) {
		position.x = SCREEN_W;
	}
	if (position.y > SCREEN_H){
		position.y == 0;
	}
	else if (position.y < 0){
		position.y = SCREEN_H;
	}
}	

bool Blob::feed(void) {
	++foodCount;
	bool birth = false;
	switch (etaryGroup) {
	case BABY_BLOB:
		if (foodCount == 3){
			foodCount = 0;
			birth = true;
		}
		break;
	case GROWN_BLOB:
		if (foodCount == 4) {
			foodCount = 0;
			birth = true;
		}
		break;
	case GOOD_OLD_BLOB:
		if (foodCount == 5) {
			foodCount = 0;
			birth = true;
		}
		break;
	}
	return birth;
}


void Blob::merge(float averageX, float averageY, float averageDirection, float averageSpeed, float deathProbGrownBlob, float deathProbOldBlob) {
	switch (etaryGroup) {
	case BABY_BLOB:
		etaryGroup = GROWN_BLOB;
		deathProb = deathProbGrownBlob;
		break;
	case GROWN_BLOB:
		etaryGroup = GOOD_OLD_BLOB;
		deathProb = deathProbOldBlob;
		break;
	case GOOD_OLD_BLOB:
		break;
	}
	position.x = averageX;
	position.y = averageY;
	direction = averageDirection;
	speed = averageSpeed;
}

void Blob::birth(Blob& blobMom, float deathProbBabyBlob, int mode, int speedMax, float speedProb) {\
	cout << "BIRTH" << endl;
	position.x = blobMom.position.x;	//ESTO HAY QUE CAMBIAR
	position.y = blobMom.position.y;
	direction = -blobMom.direction; //direccion de movimiento
	etaryGroup = BABY_BLOB;
	foodCount = 0;
	deathProb = deathProbBabyBlob;
	adjustSpeed(mode, speedMax, speedProb);
}

void Blob::destroy(Blob* b) {
	b = NULL;
}

void Blob::death() {
	double death = random(1);
	if (death < deathProb) {
		etaryGroup = DEATH;
	}
}



