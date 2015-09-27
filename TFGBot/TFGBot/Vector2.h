#pragma once

#include <utility>
#include <string>

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
	bool operator == (const Vector2 & a) const;
	static float Angle(const Vector2& from, const Vector2& to);
	float Angle() const;
	pair<float, float> Decompose(Vector2 v1, Vector2 v2);
	Vector2 RotatedBy(float ang) const;
	void Print(string);

	void Print();
	static float Dist(Vector2 a, Vector2 b);
	static bool VecEqual( const Vector2& v0, const Vector2& v1, float delta);
};