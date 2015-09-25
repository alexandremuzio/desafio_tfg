#pragma once

using namespace std;

class MathUtils {
public:
	static const float deg2rad;
	static const float rad2deg;
	static const float PI;
	static const float SQRT_2;

	MathUtils();
	~MathUtils();

	static int Sign(float);
	static float Limit(float, float, float);
	static float NormailizeAng(float);
	static float MinDeltaAng(float, float);
	static float GetAngFromVec2(float, float);
};