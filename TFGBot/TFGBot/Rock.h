#pragma once

#include "GameObject.h"

struct Rock : public GameObject {
	Rock();
	Rock(int, float, float, float, float, float);
	~Rock();
};