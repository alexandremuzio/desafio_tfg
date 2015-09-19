#include "Vector2.h"
#include <math.h>


Vector2::Vector2() {
	x = 0;
	y = 0;
}

Vector2::Vector2(double x, double y) {
	this->x = x;
	this->y = y;
}

Vector2::~Vector2() {
}

Vector2 Vector2::operator+(const Vector2 & a) const {
	return Vector2(this->x + a.x, this->y + a.y);
}

Vector2 Vector2::operator-(const Vector2 & a) const {
	return Vector2(this->x - a.x, this->y - a.y);
}

Vector2 Vector2::operator*(const double mul) const {
	return Vector2(mul *x, mul * y);
}

double Vector2::dist(Vector2 a, Vector2 b) {
	return sqrt((a.x - b.x) * (a.x - b.x) 
			  + (a.y - b.y) * (a.y - b.y));
}

double Vector2::angle(Vector2 from, Vector2 to) {
	double diffX = -from.x + to.x;
	double diffY = -from.y + to.y;

	return atan2(diffY, diffX);
}
