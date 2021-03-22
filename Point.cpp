#include "Point.h"

#include <iostream>
#include <math.h>

#define PI acos(-1)
#define MIN_DISTANCE 0.0001

#define TRUE 1
#define FALSE 0
#define RIGHTANGLE 90

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

double Point::getDistance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow((p2.y - p1.y), 2));
}

double Point::getAngle(Point p1, Point p2) {
    if (p1.x == p2.x && p1.y == p2.y) {
        printf("Can't compare angle of the same points.\n");
        return FALSE;
    }
    float angle = atan(((p2.x - p1.x) / (p2.y - p1.y))) * RIGHTANGLE * 2 / PI;  // Tomo el angulo ocmo si fuera un triangulo rectangulo
    if (angle < 0)
        angle = -angle;
    if (p2.x > p1.x && p2.y < p1.y)    // Verifico todas las posibilidades de distribuciones para obtener el angulo respecto el norte
        angle = RIGHTANGLE * 2 - angle;
    else if (p2.x<p1.x && p2.y>p1.y)
        angle = RIGHTANGLE * 4 - angle;
    else if (p2.x < p1.x && p2.y < p1.y)
        angle += RIGHTANGLE * 2;
    return angle;
}


Point Point::translate(Point p, double distance, double angle) {
    Point sign = { 1,1 };
    double complement = 2 * angle / RIGHTANGLE;

    if (angle > RIGHTANGLE * 2)
        sign.x = -sign.x;                         //Verifico si por el angulo, la coordenada en x disminuye, en cuyo caso deberia restar
    if (angle > RIGHTANGLE && angle < RIGHTANGLE * 3)
        sign.y = -sign.y;                         //Verifico si por el angulo, la coordenada en y disminuye, en cuyo caso deberia restar

    if (angle > RIGHTANGLE * 3 || (angle > RIGHTANGLE && angle < RIGHTANGLE * 2))
        complement = 1;                           // Verifico si es necesareo calcular el complemento (depende de la distribucion de los puntos en el espacio)

    while (angle >= RIGHTANGLE)
        angle -= RIGHTANGLE;  // Para obtener el angulo respecto del triangulo rectangulo

    angle = complement * RIGHTANGLE - angle;   //Calculo el complemento
    p.x += (sign.x) * (sin(angle * PI / (RIGHTANGLE * 2))) * distance;
    p.y += (sign.y) * (cos(angle * PI / (RIGHTANGLE * 2))) * distance;

    if (p.x > 0 - MIN_DISTANCE && p.x < 0)        //Para evitar el '-0'
        p.x = 0;
    if (p.y > 0 - MIN_DISTANCE && p.y < 0)
        p.y = 0;

    return p;
}

bool Point::Equal(Point p1, Point p2) {
    return (getDistanceBetweenPoints(p1, p2) < MIN_DISTANCE);
}