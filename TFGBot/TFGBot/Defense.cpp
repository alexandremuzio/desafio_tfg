#include "Defense.h"


Defense::Defense() {
}


Defense::Defense(GameState* gameState, Ship* myShip) {
	this->gameState = gameState;
	this->myShip = myShip;
	defRock = new DefenseRock(gameState, myShip);
	defWall = new DefenseWall(gameState, myShip);
	defLaser = new DefenseLaser(gameState, myShip);
	defShipSight = new DefenseShipSight(gameState, myShip);
	defFutureLaser = new DefenseFutureLaser(gameState, myShip);
	defFutureRock = new DefFutureRock(gameState, myShip);
	defCenter = new DefenseCenter(gameState, myShip);
	defOpponent = new DefenceOpponent(gameState, myShip);
	lastVel = Vector2();
}

Defense::~Defense() {
}

Vector2 Defense::GetVel() {
	Vector2 vel = Vector2();
	Vector2 dv;

	Vector2 defFutureLaserVec = defFutureLaser->GetVel();
	Vector2 defFutureRockVec = defFutureRock->GetVel();
	Vector2 defShipSightVec = defShipSight->GetVel();
	Vector2 defLaserVec = defLaser->GetVel();
	Vector2 defOpponentVec = defOpponent->GetVel();
	Vector2 defRockVec = defRock->GetVel();

	dv = defRockVec;
	//dv.Print("defRock");
	vel = vel + dv;

	//dv = defWall->GetVel();
	//dv.Print("defWall");
	///*if (defFutureLaserVec.Dist() < 100.0f && defFutureRockVec.Dist() < 100.0f)*/
	//	vel = vel + dv;

	dv = defLaserVec;
	//dv.Print("defLaser");
	vel = vel + dv;

	dv = defShipSightVec;
	//dv.Print("defShipSight");
	if (defLaserVec.Dist() < 500.0f && defRockVec.Dist() < 500.0f && defFutureLaserVec.Dist() < 500.0f)

	dv = defFutureLaserVec;
	//dv.Print("defFutureLaser");
	vel = vel + dv;

	/*dv = defOpponentVec;
	dv.Print("defOpponentVec");
	if (defRockVec.Dist() < 500.0f && defLaserVec.Dist() < 500.0f && defShipSightVec.Dist() < 500.0f && defFutureLaserVec.Dist() < 500.0f)
	vel = vel + dv;*/

	dv = defFutureRockVec;
	//dv.Print("defFutureRock");
	/*if (defShipSightVec.Dist() < 5000.0f && defLaserVec.Dist() < 2000.0f)*/
		vel = vel + dv;

	dv = defCenter->GetVel();
	//dv.Print("defCenter");
	//if (defFutureLaserVec.Dist() < 100.0f && defFutureRockVec.Dist() < 100.0f)
		vel = vel + dv;

	vel = vel*0.9f+lastVel*0.1f;

	lastVel = vel;

	return vel;
}
