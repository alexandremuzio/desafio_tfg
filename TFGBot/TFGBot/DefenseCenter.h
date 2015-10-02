#pragma once

#include "GameState.h"
#include "Ship.h"

class DefenseCenter {
private:
	GameState* gameState;
	Ship* myShip;

public:
	DefenseCenter();
	DefenseCenter(GameState*, Ship*);
	~DefenseCenter();

	Vector2 GetVel();
};

