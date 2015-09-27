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
	float acx, acy;
	Ship();
	Ship(int, float , float, float, float, float, float, float, float, int);
	~Ship();

	void CloneFrom(Ship*);
	void UpdateBeforeBot();
	void UpdateAfterBot();
	Vector2 GetDirVec();
	Vector2 GetCorrectDir(const Vector2& dir);
	Vector2 GetUpVec();
	Vector2 GetUpRightVec();
	Vector2 GetRightVec();
	Vector2 GetRightDownVec();
	Vector2 GetDownVec();
	Vector2 GetDownLeftVec();
	Vector2 GetLeftVec();
	Vector2 GetLeftUpVec();
	void PrintVel();
	void PrintVel(string s);
	void PrintPos();
	void PrintLinAc();
	void PrintLinAc(string s);
	void PrintAngAc();
};
