#include "Vector2.h"

#include <math.h>
#include "MathUtils.h"

Vector2::Vector2() {
	x = 0;
	y = 0;
}

// ang in rad
Vector2::Vector2(float ang) {
	this->x = cos(ang);
	this->y = sin(ang);
}

Vector2::Vector2(float x, float y) {
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

Vector2 Vector2::operator*(const float mul) const {
	return Vector2(mul *x, mul * y);
}

float Vector2::Angle() {
	return atan2(x, y);
}

// return (k0, k1) such that k0*v0 + k1*v1 = this
pair<float, float> Vector2::Decompose(Vector2 v0, Vector2 v1) {
	pair<float, float> p;
	p.first = (x*v1.y-y*v1.x)/(v0.x*v1.y-v0.y*v1.x);
	p.second = (x*v0.y - y*v0.x) / (v1.x*v0.y-v1.y*v0.x);
	return p;
}

// ang > 0 => counter-clockwise rotation
Vector2 Vector2::RotatedBy(float ang) {
	return Vector2(x*cos(ang)-y*sin(ang), x*sin(ang)+y*cos(ang));
}

float Vector2::Dist(Vector2 a, Vector2 b) {
	return hypot(a.x-b.x, a.y-b.y);
}

float Vector2::Angle(Vector2 from, Vector2 to) {
	float diffX = -from.x + to.x;
	float diffY = -from.y + to.y;

	return atan2(diffY, diffX);
}

Vector2 Vector2::ZERO = Vector2();
Vector2 Vector2::UP = Vector2(0.0f,1.0f);
Vector2 Vector2::UP_RIGHT = Vector2(MathUtils::SQRT_2, MathUtils::SQRT_2);
Vector2 Vector2::RIGHT = Vector2(1.0f, 0.0f);
Vector2 Vector2::RIGHT_DOWN = Vector2(MathUtils::SQRT_2, -MathUtils::SQRT_2);
Vector2 Vector2::DOWN = Vector2(0.0f, -1.0f);;
Vector2 Vector2::DOWN_LEFT = Vector2(-MathUtils::SQRT_2, -MathUtils::SQRT_2);
Vector2 Vector2::LEFT = Vector2(-1.0f, 0.0f);
Vector2 Vector2::LEFT_UP = Vector2(-MathUtils::SQRT_2, MathUtils::SQRT_2);