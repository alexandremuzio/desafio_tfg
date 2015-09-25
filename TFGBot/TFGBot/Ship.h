#pragma once

#include "GameObject.h"
#include "Vector2.h"

class ShipEstimator;

struct Ship : public GameObject {
	float ang, estimatedAng;		// (rad)
	float velAng, estimatedVelAng;	// (rad / s)
	float acAng;					// Is updated after the action be defined (rad / s^2)
	float charge;					// Check if charge load has delay
	int score;

	Ship();
	Ship(int, float , float, float, float, float, float, float, float, int);
	~Ship();

	void CloneFrom(Ship*);
	void UpdateBeforeBot();
	void UpdateAfterBot();
	Vector2 GetDirVec();
};
