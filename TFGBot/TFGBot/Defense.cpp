#include "Defense.h"


Defense::Defense() {
}


Defense::Defense(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
	defRock = new DefenseRock(gameState, myShip);
	defWall = new DefenseWall(gameState, myShip);
	defLaser = new DefenseLaser(gameState, myShip);
	defShipSight = new DefenseShipSight(gameState, myShip);
}

Defense::~Defense() {
}

Vector2 Defense::GetVel() {
	Vector2 vel = Vector2();

	vel = vel + defRock->GetVel();
	vel = vel + defWall->GetVel();
	vel = vel + defLaser->GetVel();
	vel = vel + defShipSight->GetVel();

	return vel;
}
