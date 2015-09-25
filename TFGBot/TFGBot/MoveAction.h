#pragma once

#include "Vector2.h"

class MoveAction {

public:
	
	float thrust;
	float sideThrustFront;
	float sideThrustBack;

	MoveAction();
	MoveAction(Vector2, float);
	MoveAction(float, float, float);
	MoveAction(int, float);
	~MoveAction();

	MoveAction operator+(const MoveAction& other) {
		MoveAction ma;
		ma.thrust = this->thrust+other.thrust;
		ma.sideThrustFront = this->sideThrustFront + other.sideThrustFront;
		ma.sideThrustBack = this->sideThrustBack + other.sideThrustBack;
		return ma;
	}
	void Print();
};

