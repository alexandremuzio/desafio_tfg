#include "Action.h"

Action::Action(float thrust, float sideThrustFront, float sideThrustBack, int shoot) {
	this->thrust = thrust;
	this->sideThrustFront = sideThrustFront;
	this->sideThrustBack = sideThrustBack;
	this->shoot = shoot;
}

Action::~Action() {

}
