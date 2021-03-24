#include "Point.h"

#include <iostream>

#include <cmath>

#define     PI      acos(-1)

#define MIN_DISTANCE 0.0001

#define TRUE 1
#define FALSE 0
#define RIGHTANGLE 90

using namespace std;

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Point::move(Point& offset) {
	x += offset.x;
	y += offset.y;
}

void Point::move(float x, float y) {
	//this->x += x; this es un puntero que solo es valido dentro de un metodo, vale la direccion del objeto con el que llama al metodo
	this->x += x;
	this->y += y;
}

void Point::print() {
	cout << "(" << x << ", " << y  << ")";
}

float Point::getDistance(Point& p2) {
    return  (float) (sqrt(pow(p2.x - x, 2) + pow((p2.y - y), 2)));
}

float Point::getAngle(Point& p2) {
    float angle;
    if (x == p2.x && y == p2.y) {
        //printf("Can't compare angle of the same points.\n");
        angle = 0;
        return angle;
    }
    angle = atan(((p2.x - x) / (p2.y - y))) * RIGHTANGLE * 2 / PI;  // Tomo el angulo como si fuera un triangulo rectangulo
    if (angle < 0)
        angle = -angle;
    if (p2.x > x && p2.y < y)    // Verifico todas las posibilidades de distribuciones para obtener el angulo respecto el norte
        angle = RIGHTANGLE * 2 - angle;
    else if (p2.x < x && p2.y > y)
        angle = RIGHTANGLE * 4 - angle;
    else if (p2.x < x && p2.y < y)
        angle += RIGHTANGLE * 2;
    return  (float) (angle);
}


void Point::translate(double distance, double angle) {
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
    x += (sign.x) * (sin(angle * PI / (RIGHTANGLE * 2))) * distance;
    y += (sign.y) * (cos(angle * PI / (RIGHTANGLE * 2))) * distance;

    if (x > 0 - MIN_DISTANCE && x < 0)        //Para evitar el '-0'
        x = 0;
    if (y > 0 - MIN_DISTANCE && y < 0)
        y = 0;
}

bool Point::Equal(Point& p2) {
    return (getDistance(p2) < MIN_DISTANCE);
}

bool Point::checkPointInCircle(Point& p2, float r) {
    return (getDistance(p2) <= r);
}

bool Point::checkPointInRect(Point& p2, float maxX, float maxY) {

    bool inside = false;
    double angle = getAngle(p2);
    double distance = getDistance(p2);
    double x_distance = fabs(distance * cos(angle));
    double y_distance = fabs(distance * sin(angle));
    if (x_distance < maxX || y_distance < maxY)
        inside = true;
    return inside;
}

Point Point::closerPoint(Point p[], int maxPoint) {
    int index = 0;
    double aux;
    double closer = getDistance(p[index]);
    for (int i = 1; i < maxPoint; i++) {
        aux = getDistance(p[i]);
        if (aux < closer) {
            closer = aux;
            index = i;
        }    
    }
    return p[index];
}



