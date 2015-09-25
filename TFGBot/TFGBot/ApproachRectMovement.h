#pragma once

#include "Movement.h"
#include "MoveAction.h"

class ApproachRectMovement : Movement {
	
	public:

		ApproachRectMovement();
		~ApproachRectMovement();

		MoveAction Update();
};

