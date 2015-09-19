#pragma once

#include "BotBase.h"
#include "Vector2.h"

enum State {
	TROOPER,
	SNIPER,
	DODGER
};

class Girombot : public BotBase {
public:
	Girombot();
	~Girombot();
	virtual void Process();
	void clean();

	//control/action
	void shootAtTarget(int intens, Vector2 & target);
	void thrustToAngle(double u, double angle);
	void goToAngle(double angle);

	//helper
	bool checkIfCloseFromBorder();
	GameObject* closestObjectFromSelf();

	double ms;
	bool first;
	State state;
	Vector2 pos;
};

