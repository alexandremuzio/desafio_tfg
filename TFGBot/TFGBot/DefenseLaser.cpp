#include "DefenseLaser.h"

#include "DefLaserConsts.h"

DefenseLaser::DefenseLaser() {
}


DefenseLaser::DefenseLaser(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
}

DefenseLaser::~DefenseLaser() {
}

Vector2 DefenseLaser::GetVel() {
	allVelocitys.clear();

	for (map<int, Laser*>::iterator itr = gameState->lasers.begin(); itr != gameState->lasers.end(); itr++) {
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

bool DefenseLaser::Intersect(Laser* laser) {
	Vector2 laserVel = Vector2(laser->velx, laser->vely);
	Vector2 laserToShip = Vector2(myShip->posx - laser->posx, myShip->posy - laser->posy);
	float distLaserShip = laserToShip.Dist();
	float radiusSum = DefLaserConsts::radius + laser->radius;
	if (distLaserShip <= radiusSum)
		return true;
	return abs(Vector2::Angle(laserToShip, laserVel)) < asin(radiusSum / distLaserShip);
}

Vector2 DefenseLaser::GetEscapeDir(Laser* laser) {
	Vector2 laserToShip = Vector2(myShip->posx - laser->posx, myShip->posy - laser->posy);
	Vector2 shipToLaser = laserToShip*(-1);
	Vector2 laserVel = Vector2(laser->velx, laser->vely);
	float alpha = abs(Vector2::Angle(laserVel, laserToShip));
	int sign = MathUtils::Sign(Vector2::Cross(laserToShip, laserVel));
	if (sign == 0)
		sign = 1;
	return shipToLaser.RotatedBy(sign*(alpha + MathUtils::PI / 2));
}

float DefenseLaser::GetWeightThreat(Laser* laser) {
	Vector2 laserToShip = Vector2(myShip->posx - laser->posx, myShip->posy - laser->posy);
	float distLaserShip = laserToShip.Dist();
	float laserVel = hypot(laser->velx, laser->vely);
	return DefLaserConsts::weightConst * laserVel / pow(distLaserShip, DefLaserConsts::distExp);
}
