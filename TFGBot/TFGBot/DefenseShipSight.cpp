#include "DefenseShipSight.h"

#include "DefShipSightConsts.h"

DefenseShipSight::DefenseShipSight() {
}


DefenseShipSight::DefenseShipSight(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

DefenseShipSight::~DefenseShipSight() {
}

Vector2 DefenseShipSight::GetVel() {
	allVelocitys.clear();

	for (map<int, Ship*>::iterator itr = gameState->ships.begin(); itr != gameState->ships.end(); itr++) {
		if ( itr->second->uid == myShip->uid || !Intersect(itr->second))
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

bool DefenseShipSight::Intersect(Ship* otherShip) {
	Vector2 otherShipDir = otherShip->GetDirVec();
	Vector2 otherShipToMyShip = Vector2(myShip->posx - otherShip->posx, myShip->posy - otherShip->posy);
	float distOtherShipMyShip = otherShipToMyShip.Dist();
	float radiusSum = myShip->radius*1.5f + DefShipSightConsts::laserRadius;
	if (distOtherShipMyShip <= radiusSum)
		return true;

	bool r = abs(Vector2::Angle(otherShipToMyShip, otherShipDir)) < asin(radiusSum / distOtherShipMyShip);

	if ( r == false )
		lastEscapeDir[otherShip->uid] = GetEscapeDir0(otherShip);

	return r;
}



Vector2 DefenseShipSight::GetEscapeDir(Ship* otherShip) {

	Vector2 escapeDir = GetEscapeDir0(otherShip);

	/*if (abs(Vector2::Angle(lastEscapeDir[otherShip->uid], escapeDir)) > MathUtils::PI / 2 * 1.5f) {
		escapeDir = escapeDir*-1;
	}*/

	lastEscapeDir[otherShip->uid] = escapeDir;

	return escapeDir; 
}

Vector2 DefenseShipSight::GetEscapeDir0(Ship* otherShip) {
	Vector2 OtherShipToMyShip = Vector2(myShip->posx - otherShip->posx, myShip->posy - otherShip->posy);
	Vector2 myShipToOtherShip = OtherShipToMyShip*(-1);
	Vector2 otherShipDir = Vector2(otherShip->velx, otherShip->vely);
	float alpha = abs(Vector2::Angle(otherShipDir, OtherShipToMyShip));
	int sign = MathUtils::Sign(Vector2::Cross(OtherShipToMyShip, otherShipDir));
	if (sign == 0)
		sign = 1;

	Vector2 escapeDir = myShipToOtherShip.RotatedBy(sign*(alpha + MathUtils::PI / 2));

	return escapeDir; 
}

float DefenseShipSight::GetWeightThreat(Ship* otherShip) {
	Vector2 otherShipToMyShip = Vector2(myShip->posx - otherShip->posx, myShip->posy - otherShip->posy);
	float distOtherShipMyShip = otherShipToMyShip.Dist();

	Vector2 relVel = otherShip->GetDirVec()*otherShip->charge*25.0f - myShip->GetVelVec();
	float alpha = Vector2::Angle(otherShipToMyShip, relVel);
	float relEscalarVel = relVel.Dist()*cos(alpha);
	float time = distOtherShipMyShip / relEscalarVel;

	time = MathUtils::Limit(time, 0.0000001f, 10000.0f);

	return DefShipSightConsts::weightConst * otherShip->charge / pow(time, DefShipSightConsts::distExp);
}
