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
};

#endif //POINT_H