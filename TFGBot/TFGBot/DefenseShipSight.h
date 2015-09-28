#pragma once

#include <vector>
#include <cmath>

#include "Vector2.h"
#include "GameState.h"
#include "Ship.h"

class DefenseShipSight {

private:

	vector<Vector2> allVelocitys;
	GameState* gameState;
	Ship* myShip;

public:
	
	DefenseShipSight();
	DefenseShipSight(GameState*, Ship*);
	~DefenseShipSight();

	Vector2 GetVel();
	bool Intersect(Ship*);
	Vector2 GetEscapeDir(Ship*);
	float GetWeightThreat(Ship*);
};

