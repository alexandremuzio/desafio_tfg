#pragma once

#include "GameState.h"
#include "Ship.h"

class DefenseWall {

private:

	GameState* gameState;
	Ship* myShip;

public:

	DefenseWall();
	DefenseWall(GameState*, Ship*);
	~DefenseWall();

	Vector2 GetVel();
};

