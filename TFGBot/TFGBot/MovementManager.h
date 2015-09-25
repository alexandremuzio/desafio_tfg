#pragma once

#include "MoveAction.h"

class Point;
class AlignAngMovement;
class AlignVelMovement;
class ApproachRectMovement;

class MovementManager {

private:

	float desiredLinearVel;

	AlignAngMovement* alignAngMov;
	AlignVelMovement* alignVelMov;
	ApproachRectMovement* approachRectMov;

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

	void SetDesiredLinearVel(float);

	bool AligningAng();
	bool AligningVel();
	bool ApproachingRect();
};

