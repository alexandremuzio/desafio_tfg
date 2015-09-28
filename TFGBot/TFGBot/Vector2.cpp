#include "Vector2.h"

#include <math.h>
#include <sstream>

#include "MathUtils.h"
#include "PassedGSManager.h"

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

bool Vector2::operator==(const Vector2 & a) const {
	return abs(x - a.x) < 0.001f && abs(y - a.y) < 0.001f;
}


float Vector2::Angle() const {
	return atan2(y, x);
}

// return (k0, k1) such that k0*v0 + k1*v1 = this
pair<float, float> Vector2::Decompose(Vector2 v0, Vector2 v1) {
	pair<float, float> p;

	/*stringstream ss;
	ss << "Decompose: " << endl;
	PassedGSManager::Get(0)->Log(ss.str());
	v0.Print();
	v1.Print();*/

	p.first = (x*v1.y - y*v1.x) / (v0.x*v1.y - v0.y*v1.x);
	p.second = (x*v0.y - y*v0.x) / (v1.x*v0.y - v1.y*v0.x);

	/*ss.clear();
	ss.str("");
	ss << "p.first = " << p.first << endl;
	ss << "p.second = " << p.second << endl;
	PassedGSManager::Get(0)->Log(ss.str());*/

	return p;
}

// ang > 0 => counter-clockwise rotation
Vector2 Vector2::RotatedBy(float ang) const {
	return Vector2(x*cos(ang) - y*sin(ang), x*sin(ang) + y*cos(ang));
}

void Vector2::SetLength(float newLength) {
	float currLength = hypot(x, y);
	x = x*newLength / currLength;
	y = y*newLength / currLength;
}

void Vector2::ValidVel() {
	if ( x == 0.0f )
		x = 0.000001f;
	if (y == 0.0f)
		y = 0.000001f;
}

float Vector2::Dist(Vector2 a, Vector2 b) {
	return hypot(a.x - b.x, a.y - b.y);
}

float Vector2::Dist() {
	return hypot(x, y);
}

bool Vector2::VecEqual(const Vector2& v0, const Vector2& v1, float delta) {
	return abs(v0.x - v1.x) < delta && abs(v0.y - v1.y) < delta;
}

float Vector2::Angle(const Vector2& from, const Vector2& to) {
	/*from.Print("from");
	to.Print("to");
	stringstream ss;
	ss << to.Angle() << "(to.Angle())" << endl;
	ss << from.Angle() << "(from.Angle())" << endl;
	PassedGSManager::Get(0)->Log(ss.str());*/
	return MathUtils::NormailizeAng(to.Angle() - from.Angle());
}

float Vector2::Cross(const Vector2& u, const Vector2& v) {
	return u.x*v.y - u.y*v.x;
}

void Vector2::Print() {
	stringstream ss;
	ss << "Vector2 (" << x << ", " << y << ")";
	PassedGSManager::Get(0)->Log(ss.str());
}

void Vector2::Print(string s) {
	stringstream ss;
	ss << "Vector2 (" << s << "): " << "(" << x << ", " << y << ")";
	PassedGSManager::Get(0)->Log(ss.str());
}

Vector2 Vector2::ZERO = Vector2();
Vector2 Vector2::UP = Vector2(0.0f, 1.0f);
Vector2 Vector2::UP_RIGHT = Vector2(1 / MathUtils::SQRT_2, 1 / MathUtils::SQRT_2);
Vector2 Vector2::RIGHT = Vector2(1.0f, 0.0f);
Vector2 Vector2::RIGHT_DOWN = Vector2(1 / MathUtils::SQRT_2, -1 / MathUtils::SQRT_2);
Vector2 Vector2::DOWN = Vector2(0.0f, -1.0f);;
Vector2 Vector2::DOWN_LEFT = Vector2(-1 / MathUtils::SQRT_2, -1 / MathUtils::SQRT_2);
Vector2 Vector2::LEFT = Vector2(-1.0f, 0.0f);
Vector2 Vector2::LEFT_UP = Vector2(-1 / MathUtils::SQRT_2, 1 / MathUtils::SQRT_2);