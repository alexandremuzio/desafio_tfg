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
	acAng = 0.0f;
	acx = 0.0f;
	acy = 0.0f;
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
	ang += MathUtils::PI / 2;
	ang = MathUtils::NormailizeAng(ang);

	velAng *= MathUtils::deg2rad;
}

void Ship::UpdateAfterBot() {
	// Doing at this way: pass cinematic to dynamic and after from dynamic to cinematic is inefficient
	// but do not restring the movement to acx, acy, acAng
	// acx, acy, acAng are no independent variables
	// This way in every step i calculate the exactly accelerations

	GameState* gs = PassedGSManager::Get(0);
	acAng = 1 / GameConst::J*GameConst::sideThrusterOffset *GameConst::sideThrustersForce*(-gs->GetSideThrustFront() + gs->GetSideThrustBack());

	/*stringstream ss;
	ss << "---: " << endl;
	ss << "\t" << gs->GetSideThrustFront() << "(gs->GetSideThrustFront())" << endl;
	ss << "\t" << GameConst::sideThrustersForce << "(GameConst::sideThrustersForce)";
	PassedGSManager::Get(0)->Log(ss.str());*/

	acx =	gs->GetSideThrustFront()*(GameConst::sideThrustersForce / GameConst::shipMass) +
			gs->GetSideThrustBack()*(GameConst::sideThrustersForce / GameConst::shipMass);
	acy = gs->GetThrust()*(GameConst::mainThrusterForce / GameConst::shipMass);
	Vector2 linAc = Vector2(acx, acy);

	//PrintLinAc("before rotation");

	linAc = linAc.RotatedBy(ang - Vector2::UP.Angle());
	acx = linAc.x;
	acy = linAc.y;

	//gs->PrintAction("after bot update");
	/*PrintLinAc("after bot update");
	PrintVel("after bot update");*/
}

Vector2 Ship::GetDirVec() {
	return Vector2(ang);
}

Vector2 Ship::GetCorrectDir(const Vector2& dir) {
	return dir.RotatedBy(ang-MathUtils::PI/2);
}


// Return already considering ship angle
Vector2 Ship::GetUpVec() {
	return Vector2::UP.RotatedBy(ang - MathUtils::PI/2);
}

Vector2 Ship::GetUpRightVec() {
	return Vector2::UP_RIGHT.RotatedBy(ang - MathUtils::PI/2);
}

Vector2 Ship::GetRightVec() {
	return Vector2::RIGHT.RotatedBy(ang - MathUtils::PI/2);
}

Vector2 Ship::GetRightDownVec() {
	return Vector2::RIGHT_DOWN.RotatedBy(ang - MathUtils::PI / 2);
}

Vector2 Ship::GetDownVec() {
	return Vector2::DOWN.RotatedBy(ang - MathUtils::PI / 2);
}

Vector2 Ship::GetDownLeftVec() {
	return Vector2::DOWN_LEFT.RotatedBy(ang - MathUtils::PI / 2);
}

Vector2 Ship::GetLeftVec() {
	return Vector2::LEFT.RotatedBy(ang - MathUtils::PI / 2);
}

Vector2 Ship::GetLeftUpVec() {
	return Vector2::LEFT_UP.RotatedBy(ang - MathUtils::PI / 2);
}

Vector2 Ship::GetPosVec() {
	return Vector2(posx, posy);
}

Vector2 Ship::GetVelVec() {
	return Vector2(velx, vely);
}

void Ship::PrintPos() {
	stringstream ss;
	ss << "Ship position: " << "(" << posx << ", " << posy << ")";
	PassedGSManager::Get(0)->Log(ss.str());
}

void Ship::PrintVel() {
	stringstream ss;
	ss << "Ship velocity: " << "(" << velx << ", " << vely << ")";
	PassedGSManager::Get(0)->Log(ss.str());
}

void Ship::PrintVel(string s) {
	stringstream ss;
	ss << "Ship velocity (" << s << ") : " << "(" << velx << ", " << vely << ")";
	PassedGSManager::Get(0)->Log(ss.str());
}

void Ship::PrintLinAc() {
	stringstream ss;
	ss << "Ship lin. acceleration: " << "(" << acx << ", " << acy << ")";
	PassedGSManager::Get(0)->Log(ss.str());
}

void Ship::PrintLinAc(string s) {
	stringstream ss;
	ss << "Ship lin. acceleration (" << s << ") : " << "(" << acx << ", " << acy << ")";
	PassedGSManager::Get(0)->Log(ss.str());
}

void Ship::PrintAngAc() {
	stringstream ss;
	ss << "Ship ang. acceleration: " << acAng;
	PassedGSManager::Get(0)->Log(ss.str());
}