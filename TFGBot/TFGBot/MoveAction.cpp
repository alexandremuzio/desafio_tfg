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
MoveAction::MoveAction(int dir, float ac) {
	if (dir < 4) {
		if (dir < 2) {
			if (dir == 0) {
				this->thrust = ac*GameConst::shipMass;
				this->sideThrustFront = 0.0f;
				this->sideThrustBack = 0.0f;
			}
			else { // dir == 1
				this->thrust = ac*GameConst::shipMass / MathUtils::SQRT_2;
				this->sideThrustFront = ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
				this->sideThrustBack = ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
			}
		}
		else {
			if (dir == 2) {
				this->thrust = 0.0f;
				this->sideThrustFront = ac*GameConst::shipMass / 2;
				this->sideThrustBack = ac*GameConst::shipMass / 2;
			}
			else { // dir == 3
				this->thrust = -ac*GameConst::shipMass / MathUtils::SQRT_2;
				this->sideThrustFront = ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
				this->sideThrustBack = ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
			}
		}
	}
	else {
		if (dir < 6) {
			if (dir == 4) {
				this->thrust = -ac*GameConst::shipMass;
				this->sideThrustFront = 0.0f;
				this->sideThrustBack = 0.0f;
			}
			else { // dir == 5
				this->thrust = -ac*GameConst::shipMass / MathUtils::SQRT_2;
				this->sideThrustFront = -ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
				this->sideThrustBack = -ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
			}
		}
		else {
			if (dir == 6) {
				this->thrust = 0.0f;
				this->sideThrustFront = -ac*GameConst::shipMass / 2;
				this->sideThrustBack = -ac*GameConst::shipMass / 2;
			}
			else { // dir == 7
				this->thrust = ac*GameConst::shipMass / MathUtils::SQRT_2;
				this->sideThrustFront = -ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
				this->sideThrustBack = -ac*GameConst::shipMass / (2 * MathUtils::SQRT_2);
			}
		}
	}
}

// dir is related to the ship
MoveAction::MoveAction(Vector2 dir, float ac){
	// implement
}

MoveAction::~MoveAction() {
}

void MoveAction::Print() {
	stringstream ss;
	ss << "Printing MoveAction:" << endl;
	ss << "\t" << thrust << "(thrust)";
	ss << "\t" << sideThrustFront << "(sideThrustFront)";
	ss << "\t" << sideThrustBack << "(sideThrustBack)" << endl;
	PassedGSManager::Get(0)->Log(ss.str());
}