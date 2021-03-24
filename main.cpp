
#include <iostream>
#include <ctime>
#include "World.h"

#define FOOD_BITMAP_SIZE 20
#define BABY_BITMAP_SIZE 40
#define BLOB_BITMAP_SIZE 45
#define OLD_BITMAP_SIZE 80

using namespace std;

int main() {

	srand((unsigned int)time(NULL));
	struct userData data = {
		1,
		30,
		10,
		10,
		0.5,
		0.3,
		50,
		0.5,
		0.5,
		0.5};

	World w;

	int x = 900;
	int y = 900;
	float movement = 1;

	w.createWorld(&data, x, y);

	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "(" << w.blobs[i].position.x << "," << w.blobs[i].position.y << ")" << endl;
	}
	for (int i = 0; i < data.foodCount; i++) {
		cout << "(" << w.food[i].position.x << "," << w.food[i].position.y << ")" << endl;
	}

	w.moveBlobs(movement, BABY_BITMAP_SIZE, BLOB_BITMAP_SIZE, OLD_BITMAP_SIZE, FOOD_BITMAP_SIZE, data.smellRadius);
	cout << "BLOB 0" << "(" << w.blobs[0].position.x << "," << w.blobs[0].position.y << ")" << endl;

	data.speedMax = 20;

	cout << "BLOB 0 SPEED" << w.blobs[0].speed << endl;

	w.adjustBlobsSpeed(data.mode, data.speedMax, data.speedProb);

	cout << "BLOB 0 SPEED" << w.blobs[0].speed << endl;
	 
	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "BLOB ETARY GROUP" << w.blobs[i].etaryGroup << endl;
	}
	w.killBlobs(data.deathProbBabyBlob, data.deathProbGrownBlob, data.deathProbOldBlob);

	cout << endl;

	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "BLOB ETARY GROUP" << w.blobs[i].etaryGroup << endl;
	}

	cout << endl;

	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "BLOB food count" << w.blobs[i].foodCount << endl;
	}
	w.feedBlobs(x, y, data.mode, data.speedMax, data.speedProb, BABY_BITMAP_SIZE, BLOB_BITMAP_SIZE, OLD_BITMAP_SIZE, FOOD_BITMAP_SIZE);
	cout << endl;
	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "BLOB food count" << w.blobs[i].foodCount << endl;
	}
	cout << endl;
	for (int i = 0; i < data.foodCount; i++) {
		cout << "BLOB food state" << w.food[i].state << endl;
	}
	cout << endl;
	w.manageFood(data.foodCount, x, y);

	for (int i = 0; i < data.foodCount; i++) {
		cout << "BLOB food state" << w.food[i].state << endl;
	}
	cout << endl;

	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "BLOB ETARY GROUP" << w.blobs[i].etaryGroup << endl;
	}
	cout << endl;

	w.blobCollision(BABY_BITMAP_SIZE, BLOB_BITMAP_SIZE, OLD_BITMAP_SIZE, data.randomJiggleLimit);

	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "BLOB ETARY GROUP" << w.blobs[i].etaryGroup << endl;
	}
	cout << endl;

	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "BLOB ETARY GROUP" << w.blobs[i].etaryGroup << endl;
	}
	cout << endl;

	w.moveBlobs(movement, BABY_BITMAP_SIZE, BLOB_BITMAP_SIZE, OLD_BITMAP_SIZE, FOOD_BITMAP_SIZE, data.smellRadius);
	w.blobCollision(BABY_BITMAP_SIZE, BLOB_BITMAP_SIZE, OLD_BITMAP_SIZE, data.randomJiggleLimit);

	for (int i = 0; i < data.initialBlobs; i++) {
		cout << "BLOB ETARY GROUP" << w.blobs[i].etaryGroup << endl;
	}

	w.destroyWorld();

	//Mueve blobs segun el smell radius.
	

	//Ajusta velocidad de todos los blobs segun modo de simulacion.
	

	//Actualiza contador de ticks y llama a metodo blobDeath que analiza si mata o no a un blob :(
	

	//Mantiene cantidad de comida en niveles de foodCount.
	



	return 0;
}