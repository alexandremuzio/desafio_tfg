#pragma once

#include "Vector2.h"
#include "GameState.h"
#include "Ship.h"
#include "DefenseRock.h"
#include "DefenseWall.h"
#include "DefenseLaser.h"
#include "DefenseShipSight.h"
#include "DefenseFutureLaser.h"
#include "DefFutureRock.h"
#include "DefenseCenter.h"
#include "DefenceOpponent.h"

class Defense {

private:

	GameState* gameState;
	Ship* myShip;
	DefenseRock* defRock;
	DefenseWall* defWall;
	DefenseLaser* defLaser;
	DefenseShipSight* defShipSight;
	DefenseFutureLaser* defFutureLaser;
	DefFutureRock* defFutureRock;
	DefenseCenter* defCenter;
	DefenceOpponent* defOpponent;
	Vector2 lastVel;

public:

	Defense();
	Defense(GameState*, Ship*);
	~Defense();

	Vector2 GetVel();
};

