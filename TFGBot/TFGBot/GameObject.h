#pragma once

#include "Vector2.h"

class PassedGSManager;

struct GameObject {
	int uid;
	float posx;
	float posy;
	float velx;
	float vely;
	float radius;

	GameObject();
	GameObject(int, float, float, float, float, float);
	~GameObject();

	void CloneFrom(GameObject*);
	void UpdateBeforeBot();

	Vector2 GetVelVec();
	Vector2 GetPosVec();
};