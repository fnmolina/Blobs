#ifndef __LOGIC
#define __LOGIC

#define BABYBLOB_CELL	40
#define GROWNBLOB_CELL	40	
#define OLDBLOB_CELL	40

#define FOOD_CELL	10

struct userData {
	int mode;
	int initialBlobs;
	int foodCount;
	int speedMax;
	float speedProb;
	float smellRadius;
	float randomJiggleLimit;
	float deathProbBabyBlob;
	float deathProbGrownBlob;
	float deathProbOldBlob;
};

#endif // __WORLD