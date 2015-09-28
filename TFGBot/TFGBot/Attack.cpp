#include "Attack.h"

#include "AttackConsts.h"

Attack::Attack() {

}


Attack::Attack(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

Attack::~Attack() {
}

pair<float, int> Attack::GetAngShoot() {
	pair<float, int> p;

	Ship* closestShip = GetClosestShip();

	if (closestShip == nullptr) {
		p.first = myShip->estimatedAng;
		p.second = 0;
		return p;
	}
	
	p.first = GetAng(closestShip);

	float deltaAng = abs(myShip->estimatedAng - p.first);

	p.second = 0;
	if (deltaAng < AttackConsts::minDeltaToShoot) {
		p.second = 3;
	}

	return p;
}

Ship* Attack::GetClosestShip() {
	Ship* closestShip = nullptr;
	float minDist = 10*gameState->arenaRadius;

	for (map<int, Ship*>::iterator itr = gameState->ships.begin(); itr != gameState->ships.end(); itr++) {
		if (itr->second->uid != myShip->uid && Vector2::Dist(myShip->GetPosVec(), itr->second->GetPosVec()) < minDist ) {
			minDist = Vector2::Dist(myShip->GetPosVec(), itr->second->GetPosVec());
			closestShip = itr->second;
		}
	}

	return closestShip;
}

float Attack::GetAng(Ship* otherShip) {
	Vector2 v = Vector2(otherShip->posx-myShip->posx, otherShip->posy-myShip->posy);
	return v.Angle();
}
