#include "DodgeLaserMovement.h"

#include "PassedGSManager.h"

DodgeLaserMovement::DodgeLaserMovement() {

}

DodgeLaserMovement::DodgeLaserMovement(GameObject* go) {
	/*stringstream ss;
	ss << "Init dodge!!!";
	PassedGSManager::Get(0)->Log(ss.str());*/

	go->GetPosVec().Print("posicao do objeto");
	go->GetVelVec().Print("velocidade do objeto");

	P0(GetP0(go));
	P1(GetP1(go));
	objVel = Vector2(go->velx, go->velx);
	dirToEscape = GetDirToEscape(go, myShip->estimatedAng, myShip->GetPosVec());
	myShip->GetPosVec().Print("my ship pos");
	Finish(false);
	test = 0;
}

DodgeLaserMovement::~DodgeLaserMovement() {

}

MoveAction DodgeLaserMovement::Update() {
	MoveAction ma = MoveAction(dirToEscape, 100.0f);

	test++;

	if (InSafeZone()) {
		Finish(true);
	}

	return ma;
}

bool DodgeLaserMovement::InSafeZone() {
	if (test >= 2)
		return true;
	return false;
}

Vector2 DodgeLaserMovement::GetDirToEscape(GameObject* go, float shipAng, Vector2 shipPos) {
	Vector2 p0 = GetP0(go);
	Vector2 p1 = GetP1(go);
	Vector2 p;
	Vector2 objPos = Vector2(go->posx, go->posy);

	if (Vector2::Dist(shipPos, p0) <= Vector2::Dist(shipPos, p1)) {
		p = p0;
	}
	else {
		p = p1;
	}

	Vector2 idealEscapeDir = p-objPos;

	float minDeltaAng = abs(Vector2::Angle(Vector2::UP.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir));
	Vector2 escapeDir = Vector2::UP;
	if (abs(Vector2::Angle(Vector2::UP_RIGHT.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir)) < minDeltaAng) {
		minDeltaAng = abs(Vector2::Angle(Vector2::UP_RIGHT.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir));
		escapeDir = Vector2::UP_RIGHT;
	}
	if (abs(Vector2::Angle(Vector2::RIGHT.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir)) < minDeltaAng) {
		minDeltaAng = abs(Vector2::Angle(Vector2::RIGHT.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir));
		escapeDir = Vector2::RIGHT;
	}
	if (abs(Vector2::Angle(Vector2::RIGHT_DOWN.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir)) < minDeltaAng) {
		minDeltaAng = abs(Vector2::Angle(Vector2::RIGHT_DOWN.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir));
		escapeDir = Vector2::RIGHT_DOWN;
	}
	if (abs(Vector2::Angle(Vector2::DOWN.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir) < minDeltaAng)) {
		minDeltaAng = abs(Vector2::Angle(Vector2::DOWN.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir));
		escapeDir = Vector2::DOWN;
	}
	if (abs(Vector2::Angle(Vector2::DOWN_LEFT.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir) < minDeltaAng)) {
		minDeltaAng = abs(Vector2::Angle(Vector2::DOWN_LEFT.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir));
		escapeDir = Vector2::DOWN_LEFT;
	}
	if (abs(Vector2::Angle(Vector2::LEFT.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir) < minDeltaAng)) {
		minDeltaAng = abs(Vector2::Angle(Vector2::LEFT.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir));
		escapeDir = Vector2::LEFT;
	}
	if (abs(Vector2::Angle(Vector2::LEFT_UP.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir) < minDeltaAng)) {
		minDeltaAng = abs(Vector2::Angle(Vector2::LEFT_UP.RotatedBy(shipAng - MathUtils::PI / 2), idealEscapeDir));
		escapeDir = Vector2::LEFT_UP;
	}

	escapeDir.Print("escapeDir");

	return escapeDir;
}

Vector2 DodgeLaserMovement::GetP0(GameObject* go) {
	Vector2 objVel = Vector2(go->velx, go->vely);
	Vector2 objPos = Vector2(go->posx, go->posy);
	Vector2 aux = Vector2(objVel);
	aux = aux.RotatedBy(-MathUtils::PI/2);
	aux.SetLength(go->radius);
	return aux+objPos;
}

Vector2 DodgeLaserMovement::GetP1(GameObject* go) {
	Vector2 objVel = Vector2(go->velx, go->vely);
	Vector2 objPos = Vector2(go->posx, go->posy);
	Vector2 aux = Vector2(objVel);
	aux = aux.RotatedBy(MathUtils::PI / 2);
	aux.SetLength(go->radius);
	return aux + objPos;
}
