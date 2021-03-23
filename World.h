#ifndef __WORLD
#define __WORLD

#include "logic.h"
#include "Blob.h"
#include "Point.h"
#include "Food.h"

#define	MAX_FOOD_IN_AREA	20

#define INITIAL_BLOB_SPACE	3000

class World {
public:
	Blob* blobs;
	int blobCount;	//Blobs vivos
	int lastBlob;	//
	int blobSpaceSize;

	Food* food;
	int foodInWorld;
	int foodSpaceSize;

	long int ticks;
	
	World();
	void createBlobs(userData* data);
	void addBlobs(int blobsNum);
	void createFood(int foodCount);
	void addFood(int foodCount);
	int	 createWorld(userData* data);
	void destroyWorld();

	void moveBlobs();
	void killBlobs();
	void manageFood(int foodCount);
	void feedBlobs(float deathProbBabyBlob, int mode, int speedMax, float speedProb);
	void blobFeeding(int foodToEat[], int foodNum, int blobIndex, float deathProbBabyBlob, int mode, int speedMax, float speedProb);
	bool checkFoodInArea(Point& p1, Point& p2);
	void blobCollision(float randomJiggleLimit, float deathProbGrownBlob, float deathProbOldBlob);
	void mergeBlobs(int blobsToMerge[], int blobNum, float randomJiggleLimit, float deathProbGrownBlob, float deathProbOldBlob);
	bool checkBlobsCollision(Blob& b1, Blob& b2);
	void printError(const char* message);

private:
	void printError(const char* message);
};



#endif // __WORLD

