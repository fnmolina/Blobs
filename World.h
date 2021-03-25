#ifndef __WORLD
#define __WORLD

#include "resources.h"
#include "Blob.h"
#include "Point.h"
#include "Food.h"
#include "UserData.h"

#define	MAX_FOOD_IN_AREA	2000

#define	INITIAL_BLOB_SPACE	3500


#define MAX_BLOBS_TO_COLLIDE	2000

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

	//Reserva memoria e inicializa blobs en el mundo segun parametros por userData.
	void createBlobs(userData* data, int Xsize, int Ysize);

	//Expande la cantidad de blobs disponibles en el mundo a blobsNum.
	void addBlobs(int blobsNum, int Xsize, int Ysize);

	//Reserva memoria e inicializa alimento en el mundo.
	void createFood(int foodCount, int Xsize, int Ysize);

	//Expande cantidad de comida disponible en el mundo.
	void addFood(int foodCount, int Xsize, int Ysize);

	//Crea mundo: blobs y food.
	int	 createWorld(userData* data, int Xsize, int Ysize);

	//Libera memoria reservada previamente para blobs y food.
	void destroyWorld();

	//Mueve blobs segun el smell radius.
	void moveBlobs(int Xsize, int Ysize, int babyBlobCell, int grownBlobCell, int oldBlobCell, int foodCell, float smellRadius);

	//Ajusta velocidad de todos los blobs segun modo de simulacion.
	void adjustBlobsSpeed(bool mode, int speedMax, float speedProb);

	//Actualiza contador de ticks y llama a metodo blobDeath que analiza si mata o no a un blob :(
	void killBlobs(float deathProbBabyBlob, float deathProbGrownBlob, float deathProbOldBlob);

	//Mantiene cantidad de comida en niveles de foodCount.
	void manageFood(int foodCount, int Xsize, int Ysize);

	//Chequea si hay colision entre blob y food y alimenta los blobs.
	void feedBlobs(int Xsize, int Ysize, bool mode, int speedMax, float speedProb, int babyBlobCell, int grownBlobCell, int oldBlobCell, int foodCell);

	//Alimenta al blob con toda la comida que encuentra.
	void blobFeeding(int Xsize, int Ysize, int *foodToEat, int foodNum, int blobIndex, bool mode, int speedMax, float speedProb, int babyBlobCell, int grownBlobCell, int oldBlobCell);

	//Chequea si food colisiona o se encuentra dentro del smellradius respecto al blob.
	bool checkFoodInArea(int blobIndex, Point& p2, int babyBlobCell, int grownBlobCell, int oldBlobCell, int foodCell, float smellRadius = -1);

	//Busca colisiones entre blobs.
	void blobCollision(int babyBlobCell, int grownBlobCell, int oldBlobCell, float randomJiggleLimit);

	//Realiza mergeo de blobs colisionados.
	void mergeBlobs(int blobsToMerge[], int blobNum, float randomJiggleLimit);

	//Verifica si ocurre una colision entre blobs.
	bool checkBlobsCollision(Blob& b1, Blob& b2, int babyBlobCell, int grownBlobCell, int oldBlobCell);

private:
	//Imprime mensaje de error
	void printError(const char* message);
};



#endif // __WORLD

