#ifndef POINT_H
#define POINT_H

class Point {
public:
	float x;
	float y;

	Point(float x = 0, float y = 0);

	void move(Point& offset);
	void move(float x, float y);
	void print();
	// Calcula la distancia entre puntos
	double getDistance(Point p2);
	// Calcula el angulo entre puntos
	double getAngle(Point p2);
	// Verifica si dos puntos son muy proximos
	bool Equal(Point p2);
	// Calcula un segundo punto con la distancia y el angulo de un segundo punto a este primero
	void translate(double distance, double angle);
};

#endif //POINT_H