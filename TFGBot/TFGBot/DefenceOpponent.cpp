#include "DefenceOpponent.h"


DefenceOpponent::DefenceOpponent() {
}


DefenceOpponent::DefenceOpponent(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

DefenceOpponent::~DefenceOpponent() {
}

Vector2 DefenceOpponent::GetVel() {
	allVelocitys.clear();

	for (map<int, Ship*>::iterator itr = gameState->ships.begin(); itr != gameState->ships.end(); itr++) {
		if (itr->second->uid != myShip->uid) {
			allVelocitys.push_back(GetEscapeDir(itr->second));
			allVelocitys[allVelocitys.size() - 1].SetLength(GetWeightThreat(itr->second));
		}
	}

	Vector2 sum = Vector2();
	for (int i = 0; i < allVelocitys.size(); i++) {
		sum = sum + allVelocitys[i];
	}

	return sum;
}

Vector2 DefenceOpponent::GetEscapeDir(Ship* otherShip) {
	return otherShip->GetPosVec()-myShip->GetPosVec();
}

float DefenceOpponent::GetWeightThreat(Ship* otherShip) {
	Vector2 v = otherShip->GetPosVec() - myShip->GetPosVec();
	return 10000.0f/pow(v.Dist(), 1.7f);
}

