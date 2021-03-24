
#ifndef __BLOB_H
#define __BLOB_H

#include "Point.h"
#include "resources.h"

enum BLOBS {DEATH, BABY_BLOB, GROWN_BLOB, GOOD_OLD_BLOB};

class Blob {
public:
	Point position;
	float direction; //direccion de movimiento
	int etaryGroup;
	int foodCount;
	float deathProb;
	float speed;

	//Blob();
	Blob(int mode = 1, int speedMax = 0, float speedProb = 0, float deathProbBabyBlob = 0.5);

	void adjustMovement(Point& food, double SmellRadius);

	//Ajusta velocidad de blob segun modo de simulacion.
	void adjustSpeed(int mode, int speedMax, float speedProb);

	void move(Point& food, double SmellRadius);
	bool feed(void);
	void merge(float averageX, float averageY, float averageDirection, float averageSpeed, float deathProbGrownBlob, float deathProbOldBlob);
	void birth(Blob& blobMom, float deathProbBabyBlob, int mode, int speedMax, float speedProb);
	void destroy(Blob* b);
	void death();

	//adjustMovement; -- > usa smell radius
	//moveBlobs; -- > usa movement
	//destroyBlob;
	//feedBlob;
	//grow;

};

#endif