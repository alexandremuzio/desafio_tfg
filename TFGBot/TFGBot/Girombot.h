#pragma once

#include "BotBase.h"
#include "Vector2.h"

enum State {
	TROPPER,
	SNIPER
};

class Girombot : public BotBase {
public:
	Girombot();
	~Girombot();
	virtual void process();
	void clean();

	void shootAtTarget(int intens, Vector2 & target);

	void goToAngle(double angle);

	bool checkIfCloseFromBorder();
	GameObject* closestObjectFromSelf();

	double ms;
	bool first;
	State state;
	Vector2 pos;
};

