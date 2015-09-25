#pragma once

#include <utility>

#include "Movement.h"
#include "MoveAction.h"
#include "Vector2.h"

using namespace std;

class AlignVelMovement : Movement {

private:

	MoveAction ma;	
	static int nStages;
	int stage;
	Vector2 desVel;
	Vector2 dir0, dir1;
	float amp0, amp1;

public:

	AlignVelMovement(float, float);
	~AlignVelMovement();

	MoveAction Update();
	void InitStages();
	MoveAction Stage0Update();
	MoveAction Stage1Update();
	void IncStage();
};

