#include "Point.h"

#include <iostream>

using namespace std;

Point::Point(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Point::move(Point& offset) {
	x += offset.x;
	y += offset.y;
	z += offset.z;
}

void Point::move(float x, float y, float z) {
	//this->x += x; this es un puntero que solo es valido dentro de un metodo, vale la direccion del objeto con el que llama al metodo
	this->x += x;
	this->y += y;
	this->z += z;
}

void Point::print() {
	cout << "(" << x << ", " << y << ", " << z << ")";
}