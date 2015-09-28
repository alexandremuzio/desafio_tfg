#pragma once

#include "GameState.h"
#include "Ship.h"

class Attack {

private:
	GameState* gameState;
	Ship* myShip;

public:

	Attack();
	Attack(GameState*, Ship*);
	~Attack();

	pair<float, int> GetAngShoot();

	Ship* GetClosestShip();
	float GetAng(Ship*);
};

