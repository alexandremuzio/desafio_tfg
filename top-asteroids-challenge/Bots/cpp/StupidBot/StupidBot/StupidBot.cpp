#include "StupidBot.h"
#include "PassedGSManager.h"

#include <cmath>
#include <sstream>

StupidBot::StupidBot() {

}

StupidBot::~StupidBot() {

}

void StupidBot::FirstTick() {
}

void StupidBot::Process() {
	if (gamestate->tick == 0) {
		FirstTick();
	}

	thrust = 0.0f;
	sideThrustFront = 0.0f;
	sideThrustBack = 0.0f;
	shoot = 0;

	if (gamestate->tick > 10) {
		sideThrustFront = 1.0f;
		sideThrustBack = 1.0f;
	}
}

void StupidBot::SetPassedGSManager(PassedGSManager* passedGSManager) {
	this->passedGSManager = passedGSManager;
}