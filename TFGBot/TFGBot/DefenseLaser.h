#pragma once

#include <vector>
#include <cmath>

#include "Vector2.h"
#include "GameState.h"
#include "Ship.h"
#include "Laser.h"

class DefenseLaser {

private:
	vector<Vector2> allVelocitys;
	GameState* gameState;
	Ship* myShip;

public:

	DefenseLaser();
	DefenseLaser(GameState*, Ship*);
	~DefenseLaser();

	Vector2 GetVel();
	bool Intersect(Laser*);
	Vector2 GetEscapeDir(Laser* );
	float GetWeightThreat(Laser*);
};

