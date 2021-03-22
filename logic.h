#ifndef __LOGIC
#define __LOGIC

#define BABYBLOB_CELL	
#define GROWNBLOB_CELL
#define OLDBLOB_CELL

#define FOOD_CELL

#define WORLD_SIZE

#define INITIAL_BLOB_SPACE	3000

enum BLOBS {DEATH, BABYBLOB, GROWNBLOB, OLDBLOB};

struct userData {
	int mode;
	int initialBlobs;
	int foodCount;
	float speedMax;
	float speedProb;
	float smellRadius;
	float randomJiggleLimit;
	float deathProbBabyBlob;
	float deathProbGrownBlob;
	float deathProbOldBlob;
};

#endif // __WORLD