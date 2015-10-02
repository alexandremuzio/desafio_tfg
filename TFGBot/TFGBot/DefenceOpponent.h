#pragma once

#include <vector>
#include <cmath>

#include "Vector2.h"
#include "GameState.h"
#include "Ship.h"
#include "Laser.h"

class DefenceOpponent {

private:
	vector<Vector2> allVelocitys;
	GameState* gameState;
	Ship* myShip;

public:
	DefenceOpponent();
	DefenceOpponent(GameState*, Ship*);
	~DefenceOpponent();

	Vector2 GetVel();
	bool Intersect(Ship*);
	Vector2 GetEscapeDir(Ship*);
	float GetWeightThreat(Ship*);
};

