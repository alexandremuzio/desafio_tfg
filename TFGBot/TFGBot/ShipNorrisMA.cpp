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

		if (v.Dist() < 10000.0f)
			v.SetLength(v.Dist()*0.2f);

		v.ValidVel();
		movManager->AlignVel(v.x, v.y, v.Dist());

		pair<float, int> angShoot = atk->GetAngShoot();
			movManager->AlignAng(angShoot.first);

		MoveAction ma = movManager->Update();

		thrust = ma.thrust;
		sideThrustFront = ma.sideThrustFront;
		sideThrustBack = ma.sideThrustBack;
		shoot = myShip->charge >= 2 ? angShoot.second : 0;
	}

	//stringstream ss;
	//ss << "gamestate->arenaRadius = " << gamestate->arenaRadius << endl;
	//ss << "myShip->radius = " << myShip->radius << endl;
	//gamestate->Log(ss.str());

	/*CheckDodge();*/

	/*stringstream ss;
	ss << myShip->posx << "(posx)" << endl;
	ss << myShip->posy << "(posy)" << endl;
	ss << myShip->ang << "(ang)" << endl;
	ss << myShip->velx << "(velx)" << endl;
	ss << myShip->vely << "(vely)";
	gamestate->ScenarioSwitch.Current.type(ss.str());*/

	//ma.Print();
}