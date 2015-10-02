#include "AlignAngMovement.h"

#include <sstream>

#include "MathUtils.h"
#include "Ship.h"
#include "GameConst.h"
#include "GameState.h"
#include "MoveAction.h";

AlignAngMovement::AlignAngMovement() {

}

AlignAngMovement::AlignAngMovement(float finalAng) {
	alignAngState = 2;
	initialSignVelAng = MathUtils::Sign(MathUtils::MinDeltaAng(finalAng, myShip->estimatedAng));
	this->finalAng = finalAng;

	/*stringstream ss;
	ss << initialSignVelAng;
	gamestate->Log(ss.str());*/
}

AlignAngMovement::~AlignAngMovement() {

}

MoveAction AlignAngMovement::Update() {
	float ac = 0.0f;
	/*float kx = -16.94;
	float ky = -5.32;*/
	float kx = -17.0f;
	float ky = -5.5f;
	float e1 = MathUtils::MinDeltaAng(finalAng, myShip->estimatedAng);
	float e2 = -myShip->velAng;
	float deltaAng = e1;
	float deltaAngToStop = (myShip->estimatedVelAng*myShip->estimatedVelAng) * MathUtils::Sign(myShip->estimatedVelAng) / (2 * GameConst::maxAcAng);

	/*stringstream ss;
	ss << finalAng << "(finalAng)";
	ss << "\t" << myShip->estimatedAng << "(myShip->estimatedAng)";
	gamestate->Log(ss.str());*/

	if (alignAngState == 0) {
		ac = GameConst::maxAcAng*initialSignVelAng;

		if (deltaAngToStop > deltaAng && myShip->estimatedVelAng != 0.0f)
			alignAngState++;

		lastEstimatedVelAng = myShip->velAng;
	}

	if (alignAngState == 1) {
		ac = -GameConst::maxAcAng*initialSignVelAng;

		float nextEstimatedVelAng = myShip->velAng + ac*gamestate->GetTimeStep();

		/*stringstream ss;
		ss << "\t" << (nextEstimatedVelAng) << "(nextEstimatedVelAng)";
		ss << "\t" << myShip->estimatedVelAng << "(estimatedVelAng)";
		ss << endl;
		gamestate->Log(ss.str());*/

		if (MathUtils::Sign(nextEstimatedVelAng*myShip->estimatedVelAng) != 1)
			alignAngState++;

		//lastEstimatedVelAng =  myShip->estimatedVelAng;
	}

	if (alignAngState == 2) {
		ac = -kx*e1 - ky*e2;
		ac = MathUtils::Limit(ac, -GameConst::maxAcAng, GameConst::maxAcAng);
	}

	/*stringstream ss;
	ss << (gamestate->GetTick()) << "(tick)";
	ss << "\t" << deltaAngToStop << "(deltaAngToStop)";
	ss << "\t" << deltaAng << "(deltaAng)";
	ss << "\t" << myShip->estimatedAng << "(estimatedAng)";
	ss << "\t" << myShip->estimatedVelAng << "(estimatedVelAng)";
	gamestate->Log(ss.str());*/

	return MoveAction(0.0f, -ac / GameConst::maxAcAng, ac / GameConst::maxAcAng );
}
