#pragma once

#include <vector>
#include <cmath>

#include "Vector2.h"
#include "GameState.h"
#include "Ship.h"
#include "Rock.h"

using namespace std;

class DefenseRock {

private:
	vector<Vector2> allVelocitys;
	GameState* gameState;
	Ship* myShip;

public:

	DefenseRock();
	DefenseRock(GameState*, Ship*);
	~DefenseRock();

	Vector2 GetVel();
	bool Intersect(Rock*);
	Vector2 GetEscapeDir(Rock* rock);
	float GetWeightThreat(Rock* rock);
};

