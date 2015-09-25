#pragma once

class Action {

public:

	float thrust;
	float sideThrustFront;
	float sideThrustBack;
	int shoot;

	Action(float, float, float, int);
	~Action();
};

