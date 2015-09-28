#pragma once

#include "Vector2.h"
#include "GameState.h"
#include "Ship.h"
#include "DefenseRock.h"
#include "DefenseWall.h"
#include "DefenseLaser.h"
#include "DefenseShipSight.h"

class Defense {

private:

	GameState* gameState;
	Ship* myShip;
	DefenseRock* defRock;
	DefenseWall* defWall;
	DefenseLaser* defLaser;
	DefenseShipSight* defShipSight;

public:

	Defense();
	Defense(GameState*, Ship*);
	~Defense();

	Vector2 GetVel();
};

