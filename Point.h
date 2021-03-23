#ifndef POINT_H
#define POINT_H


#define OUT_OF_RANGE    -99999

class Point {
public:
	float x;
	float y;

	Point(float x = 0, float y = 0);

	void move(Point& offset);
	void move(float x, float y);
	void print();
	// Calcula la distancia entre puntos
	double getDistance(Point& p2);
	// Calcula el angulo entre puntos
	double getAngle(Point& p2);
	// Verifica si dos puntos son muy proximos
	bool Equal(Point& p2);
	// Calcula un segundo punto con la distancia y el angulo de un segundo punto a este primero
	void translate(double distance, double angle);
	// Verifica si el punto p2 se encuentra dentro de un circulo de radio centrado en (x,y)
	bool checkPointInCircle(Point& p2, float r);
	// Verifica si el punto p2 se encuentra dentro de un rectangulo de lado 2*maxX y 2*maxY centrado en (x,y)
	bool checkPointInRect(Point& p2, float maxX, float maxY);
	// Devuelve el indice del punto mas proximo de entre un arreglo de puntos.
	Point closerPoint(Point p[], int maxPoint);
};

#endif //POINT_H