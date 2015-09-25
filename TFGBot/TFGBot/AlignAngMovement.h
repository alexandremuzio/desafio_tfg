#pragma once

#include "Movement.h"

class MoveAction;

class AlignAngMovement : Movement {

private:
	
	float finalAng;
	int alignAngState;
	int initialSignVelAng;
	float lastEstimatedVelAng;

public:

	AlignAngMovement();
	AlignAngMovement(float);
	~AlignAngMovement();

	MoveAction Update();
};

