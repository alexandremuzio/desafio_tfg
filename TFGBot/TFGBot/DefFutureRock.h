#pragma once

#include <vector>
#include <cmath>

#include "Vector2.h"
#include "GameState.h"
#include "Ship.h"
#include "Laser.h"
#include "Rock.h"

class DefFutureRock {

private:
vector<Vector2> allVelocitys;
GameState* gameState;
Ship* myShip;
float timeRatio;

public:

	DefFutureRock();
	DefFutureRock(GameState*, Ship*);
	~DefFutureRock();

	Vector2 GetVel();
	float AvoidFutureCollWeight(Rock*);
	bool CanCollide(Rock*);
	Vector2 AvoidFutureColl(Rock*);
};

