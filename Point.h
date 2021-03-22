#ifndef POINT_H
#define POINT_H

class Point {
public:
	float x;
	float y;
	float z;

	Point(float x = 0, float y = 0, float z = 0);

	void move(Point& offset);
	void move(float x, float y, float z);
	void print();
	// Calcula la distancia entre puntos
	double getDistance(Point p1, Point p2);
	// Calcula el angulo entre puntos
	double getAngle(Point p1, Point p2);
	// Verifica si dos puntos son muy proximos
	bool Equal(Point p1, Point p2);
	// Calcula un segundo punto con la distancia y el angulo de un segundo punto a este primero
	Point translate(Point p, double distance, double angle);
};

#endif //POINT_H