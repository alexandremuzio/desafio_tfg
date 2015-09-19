#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(double x, double y);
	~Vector2();

	Vector2 operator + (const Vector2 & a) const;
	Vector2 operator - (const Vector2 & a) const;
	Vector2 operator * (const double mul) const;

	static double dist(Vector2 a, Vector2 b);
	static double angle(Vector2 a, Vector2 b);

	double x, y;
};

