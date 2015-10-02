#include "DefenseFutureLaser.h"


DefenseFutureLaser::DefenseFutureLaser() {
}


DefenseFutureLaser::DefenseFutureLaser(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

DefenseFutureLaser::~DefenseFutureLaser() {

}

Vector2 DefenseFutureLaser::GetVel() {
	allVelocitys.clear();

	for (map<int, Laser*>::iterator itr = gameState->lasers.begin(); itr != gameState->lasers.end(); itr++) {
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

bool DefenseFutureLaser::CanCollide(Laser* laser) {
	Vector2 vl = laser->GetVelVec();
	Vector2 vs = myShip->GetVelVec();
	Vector2 PlMinuPs = Vector2(laser->posx - myShip->posx, laser->posy - myShip->posy);
	float m = abs(MathUtils::MinDeltaAng(vl.Angle(), PlMinuPs.Angle()));
	bool collGeometryPossible = abs(MathUtils::MinDeltaAng(vs.Angle(), PlMinuPs.Angle())) < m &&
		abs(MathUtils::MinDeltaAng(vs.Angle(), vs.Angle())) < m;
	if (!collGeometryPossible)
		return false;
	Vector2 laserToShip = Vector2(myShip->posx - laser->posx, myShip->posy - laser->posy);
	float beta = abs(Vector2::Angle(vl, laserToShip));
	float alpha = abs(Vector2::Angle(vs, laserToShip*-1));
	timeRatio = (sin(beta)*vl.Dist()) / (sin(alpha)*vs.Dist());
	return abs(timeRatio - 1.0f) < 0.5f;
}


Vector2 DefenseFutureLaser::AvoidFutureColl(Laser* laser) {
	Vector2 vl = laser->GetVelVec();
	Vector2 vs = myShip->GetVelVec();
	int sign = MathUtils::Sign(Vector2::Cross(vl, vs));

	Vector2 escapeDir = laser->GetVelVec().RotatedBy(-sign*MathUtils::PI / 2*1.1f);
	
	/*float distToArenaBoard = gameState->arenaRadius - myShip->GetPosVec().Dist();
	if (distToArenaBoard < 5.0f);
		return abs(Vector2::Angle(escapeDir, myShip->GetPosVec())) > MathUtils::PI / 2 ? escapeDir : escapeDir*-1;*/

	//if (abs(Vector2::Angle(escapeDir, myShip->GetVelVec())) > MathUtils::PI / 2 && myShip->GetVelVec().Dist() > 12.0f)
	//	return escapeDir*(-1);

	return escapeDir;
}

float DefenseFutureLaser::AvoidFutureCollWeight(Laser* laser) {
	return 1000.0f / MathUtils::Limit(abs(timeRatio - 1.0f), 0.0001f, 10000000000.0f);
}
