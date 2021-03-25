
#ifndef __BLOB_H
#define __BLOB_H

#include "Point.h"
#include "resources.h"

enum BLOBS {DEATH, BABY_BLOB, GROWN_BLOB, GOOD_OLD_BLOB, BIRTH};

class Blob {
public:
	Point position;
	float direction; 
	int etaryGroup;
	int foodCount;
	float speed;

	//Constructor de blob definido mediante argumentos por defecto.
	Blob(int Xsize = 1, int Ysize = 1, bool mode = true, int speedMax = 1, float speedProb = 0);

	//Si la distancia entre el blob y la comida es menor o igual que SmellRadius entonces se dirige hacia la comida.
	void adjustMovement(Point& food, double SmellRadius);

	//Ajusta velocidad de blob segun modo de simulacion.
	void adjustSpeed(bool mode, int speedMax, float speedProb);

	//Cambia la posicion del blob.
	void move(Point& food, double SmellRadius, int Xsize, int Ysize);

	//Controla que la posicion este dentro del espacio permitido
	void checkSpace(int Xsize, int Ysize);

	//Alimenta blob y devuelve indicador de babyBirth.
	bool feed(void);

	//Se mergean blobs en uno. Para ello se reciben datos de nuevas posiciones, direcciones y probabilidades de muerte segun evolucion de blob.
	void merge(float averageX, float averageY, float averageDirection, float averageSpeed);

	//Se produce el milagro del nacimiento de un babyBlob y se lo carga en un estado etario transitorio
	void birth(int Xsize, int Ysize, Blob& blobMom, int mode, int speedMax, float speedProb, int blobMomSize);

	//Actualiza probabilidad de muerte segun grupo etario y decide si matar a un blob.
	void death(float deathProbBabyBlob, float deathProbGrownBlob, float deathProbOldBlob);

};

#endif