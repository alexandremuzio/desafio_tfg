#pragma once

#include <utility>

using namespace std;

class Vector2 {

public:
	float x, y;
	static Vector2 ZERO;
	static Vector2 UP;
	static Vector2 UP_RIGHT;
	static Vector2 RIGHT;
	static Vector2 RIGHT_DOWN;
	static Vector2 DOWN;
	static Vector2 DOWN_LEFT;
	static Vector2 LEFT;
	static Vector2 LEFT_UP;

	Vector2();
	Vector2(float ang);
	Vector2(float x, float y);
	~Vector2();

	Vector2 operator + (const Vector2 & a) const;
	Vector2 operator - (const Vector2 & a) const;
	Vector2 operator * (const float mul) const;
	float Angle();
	pair<float, float> Decompose( Vector2 v1, Vector2 v2 );
	Vector2 RotatedBy(float ang);

	static float Dist(Vector2 a, Vector2 b);
	static float Angle(Vector2 from, Vector2 to);
};