#ifndef __WORLD
#define __WORLD

#include "resources.h"
#include "Blob.h"
#include "Point.h"
#include "Food.h"

#define	MAX_FOOD_IN_AREA	20

#define INITIAL_BLOB_SPACE	5000

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
	void createBlobs(userData* data);

	//Expande la cantidad de blobs disponibles en el mundo a blobsNum.
	void addBlobs(int blobsNum);

	//Reserva memoria e inicializa alimento en el mundo.
	void createFood(int foodCount);

	//Expande cantidad de comida disponible en el mundo.
	void addFood(int foodCount);

	//Crea mundo: blobs y food.
	int	 createWorld(userData* data);

	//Libera memoria reservada previamente para blobs y food.
	void destroyWorld();

	//Mueve blobs segun el smell radius.
	void moveBlobs(float smellRadius);

	//Ajusta velocidad de todos los blobs segun modo de simulacion.
	void adjustBlobsSpeed(int mode, int speedMax, float speedProb);

	//Actualiza contador de ticks y llama a metodo blobDeath que analiza si mata o no a un blob :(
	void killBlobs();

	//Mantiene cantidad de comida en niveles de foodCount.
	void manageFood(int foodCount);

	//Chequea si hay colision entre blob y food.
	void feedBlobs(float deathProbBabyBlob, int mode, int speedMax, float speedProb);

	//Alimenta al blob con toda la comida que encuentra.
	void blobFeeding(int foodToEat[], int foodNum, int blobIndex, float deathProbBabyBlob, int mode, int speedMax, float speedProb);

	//Chequea si food colisiona o se encuentra dentro del smellradius respecto al blob.
	bool checkFoodInArea(int blobIndex, Point& p2, float smellradious = -1);

	//Busca colisiones entre blobs.
	void blobCollision(float randomJiggleLimit, float deathProbGrownBlob, float deathProbOldBlob);

	//Realiza mergeo de blobs colisionados.
	void mergeBlobs(int blobsToMerge[], int blobNum, float randomJiggleLimit, float deathProbGrownBlob, float deathProbOldBlob);

	//Verifica si ocurre una colision entre blobs.
	bool checkBlobsCollision(Blob& b1, Blob& b2);

private:
	//Imprime mensaje de error
	void printError(const char* message);
};



#endif // __WORLD

