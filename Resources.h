#ifndef __RESOURCES
#define __RESOURCES

//image resources
#define BACKGROUND "background.jpg"
#define FOOD_SPRT "food.png"
#define BABY_SPRT "babyblob.png"
#define BLOB_SPRT "grownblob.png"
#define OLD_SPRT "goodoldblob.png"

#define FOOD_BITMAP_SIZE 20
#define BABY_BITMAP_SIZE 40
#define BLOB_BITMAP_SIZE 45
#define OLD_BITMAP_SIZE 80

#define BABYBLOB_CELL	40
#define GROWNBLOB_CELL	45	
#define OLDBLOB_CELL	80

#define FOOD_CELL		20

#define SCREEN_W	900
#define SCREEN_H	470

//font
#define FONT "Font/Font.ttf"
#define FONT_SIZE 30
#define FONT_COLOR "yellow"



struct userData {
	bool mode;
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


float random(int max);

#endif // __RESOURCES