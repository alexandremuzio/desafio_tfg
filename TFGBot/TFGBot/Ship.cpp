#include "Ship.h"
#include "MathUtils.h"
#include "PassedGSManager.h"
#include "GameConst.h"
#include "ShipEstimator.h"

Ship::Ship() {

}

Ship::Ship(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius, float _ang, float _velAng, float _charge, int _score) : GameObject(_uid, _posx, _posy, _velx, _vely, _radius) {
	ang = _ang;
	velAng = _velAng;
	charge = _charge;
	score = _score;
}

Ship::~Ship() {

};

void Ship::CloneFrom(Ship* ship) {
	GameObject::CloneFrom(ship);
	ang = ship->ang;
	velAng = ship->velAng;
	charge = ship->charge;
	score = ship->score;
	estimatedAng = ship->estimatedAng;
	estimatedVelAng = ship->estimatedVelAng;
	acAng = ship->acAng;
}

void Ship::UpdateBeforeBot() {
	GameObject::UpdateBeforeBot();
	ang *= MathUtils::deg2rad;
	ang = MathUtils::NormailizeAng(ang);
	ang += MathUtils::PI / 2;
	velAng *= MathUtils::deg2rad;
}

void Ship::UpdateAfterBot() {
	acAng = 1 / GameConst::J*GameConst::sideThrusterOffset *GameConst::sideThrustersForce*(-PassedGSManager::Get(0)->GetSideThrustFront() + PassedGSManager::Get(0)->GetSideThrustBack());

	// Print acAng
	/*stringstream ss;
	GameState* gs = PassedGSManager::Get(0);
	ss << acAng << "(acAng)";
	gs->Log(ss.str());*/
}

Vector2 Ship::GetDirVec() {
	return Vector2(ang);
}