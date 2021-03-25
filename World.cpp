#include "World.h"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

World::World() {

	blobs = NULL;
	blobCount = 0;
	lastBlob = 0;
	blobSpaceSize = 0;

	food = NULL;
	foodInWorld = 0;
	foodSpaceSize = 0;

	ticks = 0;
}

//Crea e inicializa arreglo de blobs. La inicializacion se da por el constructor de Blob.
void World::createBlobs(userData * data, int Xsize, int Ysize) {

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
			blobs[i] = Blob(Xsize, Ysize, data->mode, data->speedMax, data->speedProb);
		}
		lastBlob = blobCount - 1;	//Y se guarda la posicion del ultimo Blob vivo.
	}
	else {
		free(blobs);
		blobs = NULL;
	}
}

//Incrementa espacio para blobs en el world.
void World::addBlobs(int blobsNum, int Xsize, int Ysize) {

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
			blobs[i] = Blob(Xsize, Ysize);
			blobs[i].etaryGroup = DEATH;
		}
		lastBlob = blobCount - 1;	//Y se guarda la posicion del ultimo Blob vivo.
		blobSpaceSize = blobsNum;
	}
}

//Crea e inicializa arreglo de food. La inicializacion se da por el constructor de Food.
void World::createFood(int foodCount, int Xsize, int Ysize) {

	foodInWorld = foodCount;
	foodSpaceSize = foodCount;
	food = (Food*) malloc(sizeof(Food) * foodCount);
	if (food != NULL) {
		for (int i = 0; i < foodCount; i++) {
			food[i] = Food(Xsize, Ysize);
		}
	}
	else {
		free(blobs);
		blobs = NULL;
	}
}

//Incrementa espacio para food en el world.
void World::addFood(int foodCount, int Xsize, int Ysize) {

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
			food[i] = Food(Xsize, Ysize);
		}
	}
	foodSpaceSize = foodCount;
}

//Crea e inicializa blobs y food
int World::createWorld(userData * data, int Xsize, int Ysize) {

	createBlobs(data, Xsize, Ysize);
	if (blobs == NULL)	//si no se pudo crear blobs correctamente, se envia mensaje y señal de error.
	{
		printError("blobs");
		return 0;
	}
	createFood(data->foodCount, Xsize, Ysize); //analogo con food.
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

//Mueve todos los blobs vivos mediante el metodo move de Blob buscando la comida mas cercana.
void World::moveBlobs(float movement, int babyBlobCell, int grownBlobCell, int oldBlobCell, int foodCell, float smellRadius) {
	int f, i;
	bool collision = false;
	Point foodInArea[MAX_FOOD_IN_AREA];

	for (i = 0, f = 0; i <= lastBlob; i++, f = 0) {
		if (blobs[i].etaryGroup != DEATH) {
			//Verifica si hay alguna comida dentro del smellradius
			for (int k = 0; k < foodSpaceSize; k++) {	
				if (food[k].state != EATEN) {
					collision = checkFoodInArea(i, food[k].position, babyBlobCell, grownBlobCell, oldBlobCell, foodCell, smellRadius);
					if (collision) {
						foodInArea[f++] = food[k].position;	//Guarda posicion de blob colisionado en arreglo. 
					}
				}
			}
			if (f > 0) {	//Busca la comida mas cercana de entre todas las que estan dentro del smell radius.
				foodInArea[0] = blobs[i].position.closerPoint(foodInArea, f);	
				blobs[i].move(foodInArea[0], smellRadius, movement);
			}
			else {	//Si no se encontro comida en el rango del smellRadius, se mueve sin cambiar la direccion de movimiento.
				foodInArea[0].x = OUT_OF_RANGE;	//Se indica que el punto a comparar esta fuera de rango
				foodInArea[0].y = OUT_OF_RANGE;
			}
			blobs[i].move(foodInArea[0], smellRadius, movement);
			

		}
	}
}
//Ajusta velocidad de todos los blobs segun modo de simulacion.
void World::adjustBlobsSpeed(bool mode, int speedMax, float speedProb) {
	for (int i = 0; i < lastBlob; i++) {
		if (blobs[i].etaryGroup != DEATH) {
			blobs[i].adjustSpeed(mode, speedMax, speedProb);
		}
	}
}

//Actualiza contador de ticks y llama a metodo blobDeath que analiza si mata o no a un blob :(
void World::killBlobs(float deathProbBabyBlob, float deathProbGrownBlob, float deathProbOldBlob) {
	ticks++;
	for (int i = 0; i <= lastBlob; i++) {
		if (blobs[i].etaryGroup != DEATH) {
			blobs[i].death(deathProbBabyBlob, deathProbGrownBlob, deathProbOldBlob);
		}
	}
}


//Mantiene cantidad de comida en niveles de foodCount.
void World::manageFood(int foodCount, int Xsize, int Ysize) {
	//Si en el momento hay menos comida que foodCount, se actualizan posiciones de food.
	if (foodInWorld < foodCount) {
		for (int i = 0; i < foodSpaceSize; i++) {
			if (food[i].state == EATEN) {
				food[i] = Food(Xsize, Ysize);
			}
		}
	}
}

//Chequea si hay colision entre blob y food y alimenta los blobs.
void World::feedBlobs(int Xsize, int Ysize, bool mode, int speedMax, float speedProb, int babyBlobCell, int grownBlobCell, int oldBlobCell, int foodCell) {

	int i, f;
	bool collision = false;
	int foodToEat [MAX_FOOD_IN_AREA] = { 0 };	//Se utiliza un arreglo para guardar las posiciones de la comida colisionada.
	//Chequea si hay colision por cada blob y alimenta
	for (i = 0, f = 0; i <= lastBlob; i++, f = 0) {		//m se utiliza como indice de blobs a mergear.
		if (blobs[i].etaryGroup != DEATH) {		//Verifica si se trata de un Blob vivo.
			for (int k = 0; k < foodSpaceSize; k++) {	//De ser ese el caso, verifica si hay colision con varios food.
				if (food[k].state != EATEN) {
					collision = checkFoodInArea(i, food[k].position, babyBlobCell, grownBlobCell, oldBlobCell, foodCell);
					if (collision) {
						foodToEat[f++] = k;	//Guarda posicion de blob colisionado en arreglo. 
					}
				}
			}
			if (f > 0)
				blobFeeding(Xsize, Ysize, foodToEat, f, i, mode, speedMax, speedProb);
		}
	}
}

//Alimenta al blob con toda la comida que encuentra.
void World::blobFeeding(int Xsize, int Ysize, int * foodToEat, int foodNum, int blobIndex, bool mode, int speedMax, float speedProb) {

	int k, foodIndex, i;
	bool check = false;

	for (foodIndex = 0, i = 0; i < foodNum; i++)
	{
		foodIndex = foodToEat[i];	//se recupera el indice a la comida.
		food[foodIndex].state = EATEN;	//y se borra esa comida del mundo.
		foodInWorld--;	//decrementa contador interno de comida.

		//se llama a metodo de clase blob en el que se chequea el blob feeding y el blob birth.
		if (blobs[blobIndex].feed()) {	//En caso de producirse el milagro del blob birth, se lo posiciona en el arreglo.
			check = true;
			for (k = 0; k < blobSpaceSize && check; k++) {	
				if (blobs[k].etaryGroup == DEATH) {	//Se busca alguna posicion libre.
					blobs[k].birth(blobs[blobIndex], mode, speedMax, speedProb);
					check = false;
				}
			}
			//En caso de no haber posiciones libres en el arreglo, se agrega una nueva.
			if (k == blobSpaceSize) {
				addBlobs(k + 1, Xsize, Ysize);
				blobs[k].birth(blobs[blobIndex], mode, speedMax, speedProb);
			}
		}
	}
}	


//Los blobs recien nacidos pasan a ser babyblobs.
void World::growNewBlobs() {
	for (int i = 0; i <= lastBlob; i++) {	
		if (blobs[i].etaryGroup == BIRTH) {
			blobs[i].etaryGroup = BABY_BLOB;
		}
	}
}

//Chequea si food colisiona o se encuentra dentro del smellradius respecto al blob.
bool World::checkFoodInArea(int blobIndex, Point& p2, int babyBlobCell, int grownBlobCell, int oldBlobCell, int foodCell, float smellRadius) {
	bool check = false;
	//En caso de no haberse cargado un smellradius, por defecto se entiende que se busca chequear colision.
	if (smellRadius < 0) {
		float distance = (float) (foodCell / 2);
		//Segun el grupo etario, varia el tamano de la blobcell.
		switch (blobs[blobIndex].etaryGroup) {
		case BABY_BLOB:
			distance += (float) (babyBlobCell / 2);
			break;
		case GROWN_BLOB:
			distance += (float) (grownBlobCell / 2);
			break;
		case GOOD_OLD_BLOB:
			distance += (float) (oldBlobCell / 2);
			break;
		}
		check = blobs[blobIndex].position.checkPointInRect(p2, distance, distance);
	}
	//En caso de querer chequear si una comida esta dentro del smell radius, se calcula la distancia respecto a un circulo.
	else {
		check = blobs[blobIndex].position.checkPointInCircle(p2, smellRadius);
	}
	return check;
}

//Busca colisiones entre blobs.
void World::blobCollision(int babyBlobCell, int grownBlobCell, int oldBlobCell, float randomJiggleLimit) {

	int m, i;
	bool collision = false;
	int blobsToMerge[MAX_BLOBS_TO_COLLIDE] = { 0 };	//Se utiliza un arreglo para guardar las posiciones de los blobs colisionados.

	//Chequea si hay colision por cada blob y mergea. Notar que no hace falta comparar el ultimo blob.
	for (i = 0, m = 0; i < lastBlob; i++, m = 0) {		//m se utiliza como indice de blobs a mergear.
		if (blobs[i].etaryGroup != DEATH) {		//Verifica si se trata de un Blob vivo.
			blobsToMerge[m] = i; //Ante todo, guardo blob a comparar.
			for (int k = i + 1; k <= lastBlob; k++) {	//De ser ese el caso, verifica si hay colision con otros blobs.
				if (blobs[k].etaryGroup != DEATH) {
					collision = this->checkBlobsCollision(blobs[i], blobs[k], babyBlobCell, grownBlobCell, oldBlobCell);
					if (collision) {
						blobsToMerge[++m] = k;	//Guarda posicion de blob colisionado en arreglo. 
					}
				}
			}
			if (m > 0) {
				this->mergeBlobs(blobsToMerge, ++m, randomJiggleLimit);
			}
		}
	}
}

//Realiza mergeo de blobs colisionados.
void World::mergeBlobs(int blobsToMerge[], int blobNum, float randomJiggleLimit) {

	int i = 0;
	int blobMerged = blobsToMerge[i]; //Se realiza el mergeo sobre el primer blob analizado.
	float averageX, averageY, averageDirection, averageSpeed;
	for (int blobIndex = 0, i = 1; i < blobNum; i++) { 
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
	averageY = blobs[blobMerged].position.y / blobNum;
	averageSpeed = blobs[blobMerged].speed / blobNum;
	averageDirection = blobs[blobMerged].direction / blobNum;
	averageDirection += randomJiggleLimit;	//suma randomJiggleLimit
	if (averageDirection > 360) {	//En el caso que el angulo supere 360, se normaliza.
		averageDirection -= 360;
	}
	//Finalmente, se cambian parametros internos del blob mergeado.
	blobs[blobMerged].merge(averageX, averageY, averageDirection, averageSpeed);
}

//Verifica si ocurre una colision entre blobs.
bool World::checkBlobsCollision(Blob& b1, Blob& b2, int babyBlobCell, int grownBlobCell, int oldBlobCell) {

	bool collision = false;
	//Si los blobs comparados son del mismo grupo etario, se pasa a calcular sus distancias para luego compararlas segun el grupo etario.
	if (b1.etaryGroup == b2.etaryGroup) {
		float distance = 0;
		switch (b1.etaryGroup) {
			case BABY_BLOB:
				distance = (float) babyBlobCell;
				break;
			case GROWN_BLOB:
				distance = (float) grownBlobCell;
				break;
			case GOOD_OLD_BLOB:
				distance = (float) oldBlobCell;
				break;
		}
		collision = b1.position.checkPointInRect(b2.position, distance, distance);
	}
	return collision;
}

//Imprime mensaje de error
void World::printError(const char * message) {
	cout << "Error: couldn't initialize "<< message << " correctly." << endl;
}


