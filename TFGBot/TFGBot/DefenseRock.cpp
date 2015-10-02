#include "DefenseRock.h"

#include "DefRockConsts.h"
#include "MathUtils.h"

DefenseRock::DefenseRock() {
}


DefenseRock::DefenseRock(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

DefenseRock::~DefenseRock() {
}

Vector2 DefenseRock::GetVel() {
	allVelocitys.clear();

	for (map<int, Rock*>::iterator itr = gameState->rocks.begin(); itr != gameState->rocks.end(); itr++) {
		if (!Intersect(itr->second))
			continue;
		allVelocitys.push_back(GetEscapeDir(itr->second));
		allVelocitys[allVelocitys.size() - 1].SetLength(GetWeightThreat(itr->second));
	}

	Vector2 sum = Vector2();
	for (int i = 0; i < allVelocitys.size(); i++) {
		sum = sum + allVelocitys[i];
	}

	return sum;
}

bool DefenseRock::Intersect(Rock* rock) {
	Vector2 rockVel = Vector2(rock->velx, rock->vely);
	Vector2 rockToShip = Vector2(myShip->posx - rock->posx, myShip->posy - rock->posy);
	float distRockShip = rockToShip.Dist();
	float radiusSum = DefRockConsts::radius + rock->radius;
	if ( distRockShip <= radiusSum )
		return true;
	return abs(Vector2::Angle(rockToShip, rockVel)) < asin(radiusSum / distRockShip);
}

Vector2 DefenseRock::GetEscapeDir(Rock* rock) {
	Vector2 rockToShip = Vector2(myShip->posx-rock->posx, myShip->posy-rock->posy);
	Vector2 shipToRock = rockToShip*(-1);
	Vector2 rockVel = Vector2(rock->velx, rock->vely);
	float alpha = abs(Vector2::Angle(rockVel, rockToShip));
	int sign = MathUtils::Sign(Vector2::Cross(rockToShip, rockVel));
	if ( sign == 0 )
		sign = 1;

	Vector2 escapeDir = shipToRock.RotatedBy(sign*(alpha+MathUtils::PI*0.9f));

	float distToArenaBoard = gameState->arenaRadius - myShip->GetPosVec().Dist();
	if (distToArenaBoard < 5.0f);
		return abs(Vector2::Angle(escapeDir, myShip->GetPosVec())) > MathUtils::PI / 2 ? escapeDir : escapeDir*-1;

	return escapeDir;
}

float DefenseRock::GetWeightThreat(Rock* rock) {
	Vector2 rockToShip = Vector2(myShip->posx - rock->posx, myShip->posy - rock->posy);
	float distRockShip = rockToShip.Dist();
	Vector2 relVel = rock->GetVelVec() - myShip->GetVelVec();
	float alpha = Vector2::Angle(rockToShip, relVel);
	float relEscalarVel = relVel.Dist()*cos(alpha);
	float time = distRockShip / relEscalarVel;
	time = MathUtils::Limit(time, 0.001f, 10000.0f);

	if ( distRockShip > DefRockConsts::minDistToDefend )
		return 0.0f;
	return DefRockConsts::weightConst*rock->radius/pow(time, DefRockConsts::distExp);
}

