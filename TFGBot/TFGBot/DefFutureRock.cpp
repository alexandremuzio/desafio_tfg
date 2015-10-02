#include "DefFutureRock.h"


DefFutureRock::DefFutureRock() {
}


DefFutureRock::DefFutureRock(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

DefFutureRock::~DefFutureRock() {
}

Vector2 DefFutureRock::GetVel() {
	allVelocitys.clear();

	for (map<int, Rock*>::iterator itr = gameState->rocks.begin(); itr != gameState->rocks.end(); itr++) {
		if (itr->second->uid == myShip->uid || !CanCollide(itr->second))
			continue;
		allVelocitys.push_back(AvoidFutureColl(itr->second));
		allVelocitys[allVelocitys.size() - 1].SetLength(AvoidFutureCollWeight(itr->second));
	}

	Vector2 sum = Vector2();
	for (int i = 0; i < allVelocitys.size(); i++) {
		sum = sum + allVelocitys[i];
	}

	return sum;
}	

float DefFutureRock::AvoidFutureCollWeight(Rock* rock) {
	return 300.0f * rock->radius / MathUtils::Limit(abs(timeRatio - 1.0f), 0.0001f, 10000000000.0f);
}	

bool DefFutureRock::CanCollide(Rock* rock) {
	Vector2 vl = rock->GetVelVec();
	Vector2 vs = myShip->GetVelVec();
	Vector2 PlMinuPs = Vector2(rock->posx - myShip->posx, rock->posy - myShip->posy);
	float m = abs(MathUtils::MinDeltaAng(vl.Angle(), PlMinuPs.Angle()));
	bool collGeometryPossible = abs(MathUtils::MinDeltaAng(vs.Angle(), PlMinuPs.Angle())) < m &&
		abs(MathUtils::MinDeltaAng(vs.Angle(), vs.Angle())) < m;
	if (!collGeometryPossible)
		return false;
	Vector2 rockToShip = Vector2(myShip->posx - rock->posx, myShip->posy - rock->posy);
	float beta = abs(Vector2::Angle(vl, rockToShip));
	float alpha = abs(Vector2::Angle(vs, rockToShip*-1));
	timeRatio = (sin(beta)*vl.Dist()) / (sin(alpha)*vs.Dist());
	return abs(timeRatio - 1.0f) < 0.5f;
}

Vector2 DefFutureRock::AvoidFutureColl(Rock* rock) {
	Vector2 vl = rock->GetVelVec();
	Vector2 vs = myShip->GetVelVec();
	int sign = MathUtils::Sign(Vector2::Cross(vl, vs));
	Vector2 escapeDir = rock->GetVelVec().RotatedBy(-sign*MathUtils::PI / 2 * 1.5f);

	float distToArenaBoard = gameState->arenaRadius - myShip->GetPosVec().Dist();
	if (distToArenaBoard < 5.0f);
		return abs(Vector2::Angle(escapeDir, myShip->GetPosVec())) > MathUtils::PI / 2 ? escapeDir : escapeDir*-1;

	return escapeDir;
}

