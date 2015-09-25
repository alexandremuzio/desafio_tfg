#pragma once

#include "GameObject.h"

struct Laser : public GameObject {
	float lifetime;
	int owner;

	Laser();
	Laser(int, float, float, float, float, float, float, int);
	~Laser();
};