#ifndef __WORLD
#define __WORLD

#include "logic.h"
#include "Blob.h"
#include "Point.h"
#include "Food.h"

class World {
public:
	Blob* blobs;
	int blobCount;	//Blobs vivos
	int lastBlob;	//
	int blobSpaceSize;

	Food* food;
	int foodInWorld;
	int lastFood;

	long int ticks;
	
	World();
	void createBlobs(userData* data);
	void addBlobs(int blobsNum);
	void createFood(int foodCount);
	int	 createWorld(userData* data);
	void destroyWorld();

	void moveBlobs();
	void killBlobs();
	void manageFood(int foodCount);
	void feedBlobs(int foodCount, int maxFood);
	void blobFeeding(int foodToEat[], int foodNum, int maxFood, int blobIndex);
	bool checkFoodInArea(Point& p1, Point& p2);
	void blobCollision(int randomJiggleLimit, int deathProbGrownBlob, int deathProbOldBlob);
	void mergeBlobs(int blobsToMerge[], int blobNum, int randomJiggleLimit, int deathProbGrownBlob, int deathProbOldBlob);
	bool checkBlobsCollision(Blob& b1, Blob& b2);
	void printError(const char* message);

private:
	void printError(const char* message);
};



#endif // __WORLD

