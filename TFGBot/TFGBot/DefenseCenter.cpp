#include "DefenseCenter.h"

#include "DefWallConsts.h"

DefenseCenter::DefenseCenter() {
}


DefenseCenter::DefenseCenter(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

DefenseCenter::~DefenseCenter() {
}

Vector2 DefenseCenter::GetVel() {
	Vector2 shipToCenter = Vector2(0 - myShip->posx, 0 - myShip->posy);

	shipToCenter.SetLength(5000.0f / pow(shipToCenter.Dist(), 1.5f));
	return shipToCenter;
}
