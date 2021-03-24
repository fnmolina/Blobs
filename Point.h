#ifndef POINT_H
#define POINT_H


#define OUT_OF_RANGE    -99999

class Point {
public:
	float x;
	float y;

	//Constructor
	Point(float x = 0, float y = 0);

	//Mueve un punto con un offset
	void move(Point& offset);

	//Mueve punto mediante posiciones
	void move(float x, float y);

	//Imprime coordenadas en terminal
	void print();

	// Calcula la distancia entre puntos
	float getDistance(Point& p2);

	// Calcula el angulo entre puntos
	float getAngle(Point& p2);

	// Verifica si dos puntos son muy proximos
	bool Equal(Point& p2);

	//Translada un punto a otra posicion segun distancia y angulo.
	void translate(float distance, float angle);

	// Verifica si el punto p2 se encuentra dentro de un circulo de radio centrado en (x,y)
	bool checkPointInCircle(Point& p2, float r);

	// Verifica si el punto p2 se encuentra dentro de un rectangulo de lado 2*maxX y 2*maxY centrado en (x,y)
	bool checkPointInRect(Point& p2, float maxX, float maxY);

	// Devuelve el indice del punto mas proximo de entre un arreglo de puntos.
	Point closerPoint(Point p[], int maxPoint);
};

#endif //POINT_H