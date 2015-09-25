#include "MathUtils.h"

#include <algorithm>
#include <sstream>
#include "PassedGSManager.h"

MathUtils::MathUtils() {

}

MathUtils::~MathUtils() {

}

int MathUtils::Sign(float n) {
	if (n > 0)
		return 1;
	else if (n < 0)
		return -1;
	return 0;
}

float MathUtils::Limit(float n, float  a, float b) {
	n = min(n, b);
	n = max(n, a);
	return n;
}

// Return value belong [-PI, PI]
float MathUtils::NormailizeAng(float ang) {
	return remainderf(ang, 2 * PI);
}

// Suppose that the angles are normalized and in rad
float MathUtils::MinDeltaAng(float finalAng, float initialAng) {
	float deltaAng = finalAng - initialAng;
	if (finalAng > initialAng) {
		if ( deltaAng > PI )
			return deltaAng - 2*PI;
		return deltaAng;
	}
	else if (finalAng < initialAng) {
		if ( deltaAng < -PI )
			return deltaAng + 2*PI;
		return deltaAng;
	}
	return 0.0f;
}

float MathUtils::GetAngFromVec2(float vx, float vy) {
	if ( vx == 0.0f )
		return PI/2*Sign(vy);

	float ang = atan(vy/vx);

	/*stringstream ss1;
	ss1 << atan(vy / vx) << "(atan(vy/vx))";
	PassedGSManager::Get(0)->Log(ss1.str());*/

	if ( vx < 0.0f )
		ang += PI;

	/*stringstream ss2;
	ss2 << ang << "(ang after if)";
	PassedGSManager::Get(0)->Log(ss2.str());*/
	
	ang = NormailizeAng(ang);

	/*stringstream ss3;
	ss3 << ang << "(ang after normalization)";
	PassedGSManager::Get(0)->Log(ss3.str());*/

	return ang;
}

const float MathUtils::rad2deg =	57.295779f;
const float MathUtils::deg2rad =	 0.017453f;
const float MathUtils::PI =			 3.141592f;
const float MathUtils::SQRT_2 =		 1.414213f;