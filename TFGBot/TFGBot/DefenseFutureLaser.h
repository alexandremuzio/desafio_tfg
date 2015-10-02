#pragma once

#include <vector>
#include <cmath>

#include "Vector2.h"
#include "GameState.h"
#include "Ship.h"
#include "Laser.h"

class DefenseFutureLaser {

private:
	vector<Vector2> allVelocitys;
	GameState* gameState;
	Ship* myShip;
	float timeRatio;

public:

	DefenseFutureLaser();
	~DefenseFutureLaser();

	DefenseFutureLaser(GameState*, Ship*);
	
	Vector2 GetVel();
	float AvoidFutureCollWeight(Laser*);
	bool CanCollide(Laser*);
	Vector2 AvoidFutureColl(Laser*);
};

