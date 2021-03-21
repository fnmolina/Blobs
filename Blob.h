
#ifndef __BLOB_H
#define __BLOB_H

#include "Point.h"

#define BABY_BLOB 1
#define GROWN_BLOB 2
#define GOOD_OLD_BLOB 3

class Blob {
	Point position;
	double blobMovement; //direccion de movimiento
	int etaryGroup;
	int foodCount;
	double blobDeathProb;
	double maxSpeed; //especialmente para modo 2


	Blob();

	//void adjustMovement();
	//void move();
	void feed(void);
	void grow(void);
	//void destroy();

	//adjustMovement; -- > usa smell radius
	//moveBlobs; -- > usa movement
	//destroyBlob;
	//feedBlob;
	//grow;

};

#endif