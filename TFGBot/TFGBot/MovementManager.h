#pragma once

#include "MoveAction.h"

class Point;
class AlignAngMovement;
class AlignVelMovement;
class ApproachRectMovement;
class DodgeLaserMovement;
class GameObject;

class MovementManager {

private:
	Vector2 lastVel;
	float desiredLinearVel;

	AlignAngMovement* alignAngMov;
	AlignVelMovement* alignVelMov;
	ApproachRectMovement* approachRectMov;
	DodgeLaserMovement* dodgeMov;

public:

	MovementManager();
	MovementManager(float);
	~MovementManager();

	MoveAction Update();

	void AlignAng(float);
	void AlignAng(float, float);
	void AlignVel(float);
	void AlignVel(float, float);
	void ApproachRect(Point*, float);
	void ApproachRect(Point*, Point*);
	void Dodge(GameObject*);
	void FinishDodge();

	void SetDesiredLinearVel(float);

	bool AligningAng();
	bool AligningVel();
	bool ApproachingRect();
	bool Dodging();
};

