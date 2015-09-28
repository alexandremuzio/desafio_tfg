#pragma once
#include "Movement.h"
#include "Vector2.h"
#include "MoveAction.h"
#include "MovementManager.h"
#include "GameObject.h"

class DodgeLaserMovement : Movement {

private:
	Vector2 objVel;
	Vector2 p0, p1;
	Vector2 dirToEscape; // related to ship direction: UP means dirShip...
	bool finish;
	int test;

public:

	DodgeLaserMovement();
	DodgeLaserMovement(GameObject* go);
	~DodgeLaserMovement();

	MoveAction Update();
	bool InSafeZone();

	Vector2 GetDirToEscape(GameObject*, float, Vector2);
	Vector2 GetP0(GameObject*);
	Vector2 GetP1(GameObject*);
	
	// Getters & Setters
	Vector2 ObjVel() const { return objVel; }
	void ObjVel(Vector2 val) { objVel = val; }

	Vector2 P0() const { return p0; }
	void P0(Vector2 val) { p0 = val; }

	Vector2 P1() const { return p1; }
	void P1(Vector2 val) { p1 = val; }

	Vector2 DirToEscape() const { return dirToEscape; }
	void DirToEscape(Vector2 val) { dirToEscape = val; }
	
	bool Finish() const { return finish; }
	void Finish(bool val) { finish = val; }
};

