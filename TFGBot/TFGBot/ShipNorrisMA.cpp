#include "ShipNorrisMA.h"

#include <sstream>

#include "GameConst.h"
#include "PassedGSManager.h"
#include "MathUtils.h"
#include "MovementManager.h"

ShipNorrisMA::ShipNorrisMA() {

}

ShipNorrisMA::~ShipNorrisMA() {

}

void ShipNorrisMA::FirstTick() {
	movementManager = new MovementManager();
	movementManager->SetDesiredLinearVel(10);
	movementManager->AlignAng(90*MathUtils::deg2rad);
}

void ShipNorrisMA::Process() {
	MoveAction ma;

	if (gamestate->tick == 0) {
		FirstTick();
	}
	else {
		ma = movementManager->Update();
	}

	/*thrust = (gamestate->tick > 100 ? 1.0f : 0.0f);*/
	thrust = ma.thrust;
	sideThrustFront = ma.sideThrustFront;
	sideThrustBack = ma.sideThrustBack;
	shoot = 0;

	/*stringstream ss;
	ss << myShip->posx << "(posx)";
	ss << "\t" << myShip->posy << "(posy)";
	gamestate->Log(ss.str());*/
}