#ifndef __RESOURCES
#define __RESOURCES


#define SCREEN_W	100
#define SCREEN_H	100


//image resources
#define BACKGROUND "background.jpg"
#define FOOD_SPRT "food.png"
#define BABY_SPRT "babyblob.png"
#define BLOB_SPRT "grownblob.png"
#define OLD_SPRT "goodoldblob.png"



//font
#define FONT "Font/stupid.ttf"
#define FONT_SIZE 30
#define FONT_COLOR "white"


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


float random(int max);






#endif // __RESOURCES

