#include "MoveAction.h"

#include <sstream>

#include "PassedGSManager.h"
#include "GameConst.h"

using namespace std;

MoveAction::MoveAction() {
	this->thrust = 0.0f;
	this->sideThrustFront = 0.0f;
	this->sideThrustBack = 0.0f;
}

MoveAction::MoveAction(float thrust, float sideThrustFront, float sideThrustBack) {
	this->thrust = thrust;
	this->sideThrustFront = sideThrustFront;
	this->sideThrustBack = sideThrustBack;
}

// dir is related to the ship
MoveAction::MoveAction(Vector2 dir, float ac){
	/*stringstream ss;
	ss << "creating new MoveAction:" << endl;
	ss << "acceleration = " << ac;
	PassedGSManager::Get(0)->Log(ss.str());
	dir.Print("direction");*/

	/*dir.Print();

	stringstream ss;
	ss << "ac = " << ac << endl;
	PassedGSManager::Get(0)->Log(ss.str());*/

	if (dir == Vector2::UP) {
		this->thrust = ac*GameConst::shipMass;
		this->sideThrustFront = 0.0f;
		this->sideThrustBack = 0.0f;
	}
	else if (dir == Vector2::UP_RIGHT) {
		this->thrust = ac*GameConst::shipMass / MathUtils::SQRT_2;
		this->sideThrustFront = ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
		this->sideThrustBack = ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
	}
	else if (dir == Vector2::RIGHT) {
		this->thrust = 0.0f;
		this->sideThrustFront = ac*GameConst::shipMass / 2;
		this->sideThrustBack = ac*GameConst::shipMass / 2;
	}
	else if (dir == Vector2::RIGHT_DOWN) {
		this->thrust = -ac*GameConst::shipMass / MathUtils::SQRT_2;
		this->sideThrustFront = ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
		this->sideThrustBack = ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
	}
	else if (dir == Vector2::DOWN) {
		this->thrust = -ac*GameConst::shipMass;
		this->sideThrustFront = 0.0f;
		this->sideThrustBack = 0.0f;
	}
	else if (dir == Vector2::DOWN_LEFT) {
		this->thrust = -ac*GameConst::shipMass / MathUtils::SQRT_2;
		this->sideThrustFront = -ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
		this->sideThrustBack = -ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
	}
	else if (dir == Vector2::LEFT) {
		this->thrust = 0.0f;
		this->sideThrustFront = -ac*GameConst::shipMass / 2;
		this->sideThrustBack = -ac*GameConst::shipMass / 2;
	}
	else if (dir == Vector2::LEFT_UP) {
		this->thrust = ac*GameConst::shipMass / MathUtils::SQRT_2;
		this->sideThrustFront = -ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
		this->sideThrustBack = -ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
	}

	this->thrust /= GameConst::mainThrusterForce;
	this->sideThrustFront /= GameConst::sideThrustersForce;
	this->sideThrustBack /= GameConst::sideThrustersForce;

	//Print();
}

MoveAction::~MoveAction() {
}

void MoveAction::Print() {
	stringstream ss;
	ss << "MoveAction:" << "(" << thrust << ", " << sideThrustFront << ", " << sideThrustBack << ")";
	PassedGSManager::Get(0)->Log(ss.str());
}