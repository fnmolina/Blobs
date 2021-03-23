#include "World.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

World::World() {

	blobs = NULL;
	blobCount = 0;
	lastBlob = 0;

	food = NULL;
	foodInWorld = 0;
	foodSpaceSize = 0;

	ticks = 0;
}

//Crea e inicializa arreglo de blobs. La inicializacion se da por el constructor de Blob.
void World::createBlobs(userData * data) {

	//Se crea el espacio de blobs con una cantidad definida
	blobCount = data->initialBlobs;
	blobs = (Blob*) malloc(sizeof(Blob) * INITIAL_BLOB_SPACE);
	//Se inicializan los blobs
	if (blobs != NULL) {
		blobSpaceSize = INITIAL_BLOB_SPACE; 
		for (int i = INITIAL_BLOB_SPACE - 1; i >= blobCount; i--) {	//Primeramente, se crean e inicializan a los blobs sobrantes como muertos.
			blobs[i] = Blob();
			blobs[i].etaryGroup = DEATH;
		}
		for (int i = 0; i < blobCount; i++) {	//Luego, se crean e inicializan los blobs iniciales.
			blobs[i] = Blob(data->mode, data->speedMax, data->speedProb, data->deathProbBabyBlob);
		}
		lastBlob = blobCount - 1;	//Y se guarda la posicion del ultimo Blob vivo.
	}
	else {
		free(blobs);
		blobs = NULL;
	}
}

//Incrementa espacio para blobs en el world.
void World::addBlobs(int blobsNum) {

	blobCount = blobsNum;
	//Crea puntero auxiliar y realiza proceso de realloc.
	Blob* blobsTemp = NULL;		
	blobsTemp = (Blob*) realloc(blobs, sizeof(Blob) * blobsNum);
	if (blobsTemp != NULL) {
		blobs = blobsTemp;
	}
	else
	{
		this->printError("blobs new size");
		free(blobs);
		free(blobsTemp);
		blobs = NULL;
	}
	//Se inicializan los nuevos blobs.
	if (blobs != NULL) {
		for (int i = blobSpaceSize - 1; i >= lastBlob; i--) {	//Se crean e inicializan a los blobs sobrantes como muertos.
			blobs[i] = Blob();
			blobs[i].etaryGroup = DEATH;
		}
		lastBlob = blobCount - 1;	//Y se guarda la posicion del ultimo Blob vivo.
		blobSpaceSize = blobsNum;
	}
}

//Crea e inicializa arreglo de food. La inicializacion se da por el constructor de Food.
void World::createFood(int foodCount) {

	foodInWorld = foodCount;
	foodSpaceSize = foodCount;
	food = (Food*) malloc(sizeof(Food) * foodSpaceSize);
	if (food != NULL) {
		for (int i = 0; i < foodCount; i++) {
			food[i] = Food();
		}
	}
	else {
		free(blobs);
		blobs = NULL;
	}
}

//Incrementa espacio para food en el world.
void World::addFood(int foodCount) {

	foodInWorld = foodCount;
	
	//Crea puntero auxiliar y realiza proceso de realloc.
	Food* foodTemp = NULL;
	foodTemp = (Food*)realloc(food, sizeof(Food) * foodInWorld);
	if (foodTemp != NULL) {
		food = foodTemp;
	}
	else
	{
		this->printError("food new size");
		free(food);
		free(foodTemp);
		food = NULL;
	}
	//Se inicializan los nuevos blobs.
	if (food != NULL) {
		for (int i = foodCount - 1; i > foodSpaceSize - 1; i--) {	//Se crean e inicializan a los food sobrantes.
			food[i] = Food();
		}
	}
	foodSpaceSize = foodCount;
}

//Crea e inicializa blobs y food
int World::createWorld(userData * data) {

	createBlobs(data);
	if (blobs == NULL)	//si no se pudo crear blobs correctamente, se envia mensaje y se�al de error.
	{
		printError("blobs");
		return 0;
	}
	createFood(data->foodCount); //analogo con food.
	if (food == NULL)
	{
		printError("food");
		return 0;
	}
	return 1;
}

//Limpia datos miembros de World y libera memoria para blobs y food.
void World::destroyWorld() {

	free(blobs);
	blobs = NULL;
	blobCount = 0;
	lastBlob = 0;
	blobSpaceSize = 0;

	free(food);
	food = NULL;
	foodInWorld = 0;
	foodSpaceSize = 0;

	ticks = 0;
}

//Mueve todos los blobs vivos mediante el metodo move de Blob.
void World::moveBlobs() {

	for (int i = 0; i <= lastBlob; i++) {
		if (blobs[i].etaryGroup != DEATH) {
			blobs[i].move();
		}
	}
}

//Actualiza contador de ticks y llama a metodo blobDeath que analiza si mata o no a un blob :(
void World::killBlobs() {
	ticks++;
	for (int i = 0; i <= lastBlob; i++) {
		if (blobs[i].etaryGroup != DEATH) {
			blobs[i].death();
		}
	}
}


//Mantiene cantidad de comida en niveles de foodCount.
void World::manageFood(int foodCount) {
	//Si en el momento hay menos comida que foodCount, se actualizan posiciones de food.
	if (foodInWorld < foodCount) {
		for (int i = 0; i < foodSpaceSize; i++) {
			if (food[i].state == EATEN) {
				food[i] = Food();
			}
		}
	}
}

//Cheque si hay colision entre blob y food.
void World::feedBlobs(float deathProbBabyBlob, int mode, int speedMax, float speedProb) {

	bool collision = false;
	int foodToEat[MAX_FOOD_IN_AREA];	//Se utiliza un arreglo para guardar las posiciones de la comida colisionada.
	//Chequea si hay colision por cada blob y alimenta
	for (int i = 0, int f = 0; i <= lastBlob; i++, f = 0) {		//m se utiliza como indice de blobs a mergear.
		if (blobs[i].etaryGroup != DEATH) {		//Verifica si se trata de un Blob vivo.
			for (int k = 0; k < foodSpaceSize; k++) {	//De ser ese el caso, verifica si hay colision con varios food.
				if (food[k].state != EATEN) {
					collision = checkFoodInArea(blobs[i].position, food[k].position);
					if (collision) {
						foodToEat[f++] = k;	//Guarda posicion de blob colisionado en arreglo. 
					}
				}
			}
			if (f > 0)
				blobFeeding(foodToEat, f, i, deathProbBabyBlob, mode, speedMax, speedProb);
		}
	}
}

//Alimenta al blob con toda la comida que encuentra.
void World::blobFeeding(int foodToEat[], int foodNum, int blobIndex, float deathProbBabyBlob, int mode, int speedMax, float speedProb) {

	int k, foodIndex, i;

	for (foodIndex = 0, i = 0; i < foodNum; i++)
	{
		foodIndex = foodToEat[i];	//se recupera el indice a la comida.
		food[foodIndex].state = EATEN;	//y se borra esa comida del mundo.
		foodInWorld--;	//decrementa contador interno de comida.

		//se llama a metodo de clase blob en el que se chequea el blob feeding y el blob birth.
		if (blobs[blobIndex].feed()) {	//En caso de producirse el milagro del blob birth, se lo posiciona en el arreglo.
			for (k = 0; k < blobSpaceSize; k++) {	
				if (blobs[k].etaryGroup == DEATH) {	//Se busca alguna posicion libre.
					blobs[k].birth(blobs[blobIndex], deathProbBabyBlob, mode, speedMax, speedProb);
				}
			}
			//En caso de no haber posiciones libres en el arreglo, se agrega una nueva.
			if (k == blobSpaceSize) {
				addBlobs(k + 1);
				blobs[k].birth(blobs[blobIndex], deathProbBabyBlob, mode, speedMax, speedProb);
			}
		}
	}
}

//Chequea colision entre blob y food.
bool World::checkFoodInArea(Point& p1, Point& p2) {

	bool collision = false;
	float angle = p1.getAngle(p2);
	float distance = p1.getDistance(p2);
	float x_distance = fabs(distance * cos(angle));
	float y_distance = fabs(distance * sin(angle));
	if (x_distance < (BABYBLOB_CELL/2 + FOOD_CELL/2) || y_distance < (BABYBLOB_CELL / 2 + FOOD_CELL / 2))
		collision = true;
	return collision;
}

//Busca colisiones entre blobs.
void World::blobCollision(float randomJiggleLimit, float deathProbGrownBlob, float deathProbOldBlob) {

	bool collision = false;
	int blobsToMerge[INITIAL_BLOB_SPACE];	//Se utiliza un arreglo para guardar las posiciones de los blobs colisionados.

	//Chequea si hay colision por cada blob y mergea. Notar que no hace falta comparar el ultimo blob.
	for (int i = 0, int m = 0; i < lastBlob; i++, m = 0) {		//m se utiliza como indice de blobs a mergear.
		if (blobs[i].etaryGroup != DEATH) {		//Verifica si se trata de un Blob vivo.
			blobsToMerge[m] = i; //Ante todo, guardo blob a comparar.
			for (int k = i + 1; k <= lastBlob; k++) {	//De ser ese el caso, verifica si hay colision con otros blobs.
				if (blobs[k].etaryGroup != DEATH) {
					collision = this->checkBlobsCollision(blobs[i], blobs[k]);
					if (collision) {
						blobsToMerge[++m] = k;	//Guarda posicion de blob colisionado en arreglo. 
					}
				}
			}
			if(m > 0)
				this->mergeBlobs(blobsToMerge, ++m, randomJiggleLimit, deathProbGrownBlob, deathProbOldBlob);
		}
	}
}

//Realiza mergeo de blobs colisionados.
void World::mergeBlobs(int blobsToMerge[], int blobNum, float randomJiggleLimit, float deathProbGrownBlob, float deathProbOldBlob) {

	int i = 0;
	int blobMerged = blobsToMerge[i]; //Se realiza el mergeo sobre el primer blob analizado.
	float averageX, averageY, averageDirection, averageSpeed;
	for (int blobIndex = 0, i = 1; i < blobNum; i++)
	{ 
		blobIndex = blobsToMerge[i];
		blobs[blobMerged].position.x += blobs[blobIndex].position.x; //Se guardan las posiciones y las direcciones promedio.
		blobs[blobMerged].position.y += blobs[blobIndex].position.y;
		blobs[blobMerged].direction += blobs[blobIndex].direction;
		blobs[blobMerged].speed += blobs[blobIndex].speed;
		blobs[blobIndex].etaryGroup = DEATH;	//El blob contra el cual se colisiona pasa a estar muerto.
		blobCount--;	//De modo que se decrementan la cantidad de blobs vivos.
		if (blobIndex == lastBlob) {	//Y en el caso de ser mergeado el ultimo blob del arreglo, se reduce el flag de lastBlob.
			lastBlob--;
		}
	}
	averageX = blobs[blobMerged].position.x / blobNum;
	averageY = blobs[blobMerged].position.x / blobNum;
	averageSpeed = blobs[blobMerged].speed / blobNum;
	averageDirection = blobs[blobMerged].direction / blobNum;
	averageDirection += randomJiggleLimit;	//suma randomJiggleLimit
	if (averageDirection > 360)	//En el caso que el angulo supere 360, se normaliza.
		averageDirection -= 360;
	//Finalmente, se cambian parametros internos del blob mergeado.
	blobs[blobMerged].merge(averageX, averageY, averageDirection, averageSpeed, deathProbGrownBlob, deathProbOldBlob);
}

//Verifica si ocurre una colision entre blobs.
bool World::checkBlobsCollision(Blob& b1, Blob& b2) {

	float angle, distance, x_distance, y_distance;
	bool collision = false;
	//Si los blobs comparados son del mismo grupo etario, se pasa a calcular sus distancias para luego compararlas segun el grupo etario.
	if (b1.etaryGroup == b2.etaryGroup) {
		angle = b1.position.getAngle(b2.position);
		distance = b1.position.getDistance(b2.position);
		x_distance = fabs(distance * cos(angle));
		y_distance = fabs(distance * sin(angle));
		if (b1.etaryGroup == BABY_BLOB) {
			if (x_distance < BABYBLOB_CELL || y_distance < BABYBLOB_CELL)
				collision = true;
		}
		else if (b1.etaryGroup == GROWN_BLOB) {
			if (x_distance < GROWNBLOB_CELL || y_distance < GROWNBLOB_CELL)
				collision = true;
		}
		else if (b1.etaryGroup == GOOD_OLD_BLOB) {
			if (x_distance < OLDBLOB_CELL || y_distance < OLDBLOB_CELL)
				collision = true;
		}
	}
	return collision;
}

//Imprime mensaje de error
void World::printError(const char * message) {
	cout << "Error: couldn't initialize "<< message << " correctly." << endl;
}


/*
//ESTO VA EN POINT

double Point::getAngleBetweenPoints(Point p1, Point p2){

	double angle = (180 / PI) * atan2((p1.y - p2.y), (p1.x - p2.x));
	if (angle < 0)
		angle *= -1;
	return angle;
}

double Point::getDistanceBetweenPoints(Point p1, Point p2){

	return(sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)));
}

*/

