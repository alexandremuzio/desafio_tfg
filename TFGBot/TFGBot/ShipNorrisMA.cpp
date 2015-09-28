#include "ShipNorrisMA.h"

#include <sstream>

#include "GameConst.h"
#include "PassedGSManager.h"
#include "MathUtils.h"
#include "MovementManager.h"
#include "Vector2.h"

ShipNorrisMA::ShipNorrisMA() {
		
}

ShipNorrisMA::~ShipNorrisMA() {

}

void ShipNorrisMA::FirstTick() {
	movManager = new MovementManager();
	def = new Defense(gamestate, myShip);
	atk = new Attack(gamestate, myShip);
}

//void ShipNorrisMA::CheckDodge() {
//	if ( movManager->Dodging() )
//		return;
//
//	GameObject* go;
//	for (map<int, Rock*>::iterator itr = gamestate->rocks.begin(); itr != gamestate->rocks.end(); itr++) {
//		
//	}
//	for (map<int, Laser*>::iterator itr = gamestate->lasers.begin(); itr != gamestate->lasers.end(); itr++) {
//		go = (GameObject*)(itr->second);
//		if (NeedDodgeFrom(go)) {
//			movManager->Dodge(go);
//			return;
//		}
//	}
//}

//bool ShipNorrisMA::NeedDodgeFrom(GameObject* go) {
//	Vector2 pos = Vector2(go->posx, go->posy);
//	if ( Vector2::Dist(pos, myShip->GetPosVec()) < 50.0f + myShip->radius + go->radius )
//		return true;
//	return false;
//}

void ShipNorrisMA::Process() {

	if (gamestate->tick == 0) {
		FirstTick();
	}
	else {
		Vector2 v = def->GetVel();
		v.ValidVel();
		movManager->SetDesiredLinearVel(v.Dist());
		movManager->AlignVel(v.x, v.y);

		pair<float, int> angShoot = atk->GetAngShoot();
		movManager->AlignAng(angShoot.first);

		MoveAction ma = movManager->Update();

		thrust = ma.thrust;
		sideThrustFront = ma.sideThrustFront;
		sideThrustBack = ma.sideThrustBack;
		shoot = angShoot.second;
	}

	/*CheckDodge();*/

	/*stringstream ss;
	ss << myShip->posx << "(posx)" << endl;
	ss << myShip->posy << "(posy)" << endl;
	ss << myShip->ang << "(ang)" << endl;
	ss << myShip->velx << "(velx)" << endl;
	ss << myShip->vely << "(vely)";
	gamestate->Log(ss.str());*/

	//ma.Print();
}