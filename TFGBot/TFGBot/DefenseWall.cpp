#include "DefenseWall.h"

#include "DefWallConsts.h"

DefenseWall::DefenseWall() {
}


DefenseWall::DefenseWall(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

DefenseWall::~DefenseWall() {
}

Vector2 DefenseWall::GetVel() {
	Vector2 shipToCenter = Vector2(0 - myShip->posx, 0 - myShip->posy);
	float distToWall = gameState->arenaRadius - shipToCenter.Dist();
	shipToCenter.SetLength(DefWallConsts::weightConst / pow(distToWall, DefWallConsts::distExp));
	return shipToCenter;
	return Vector2();
}
