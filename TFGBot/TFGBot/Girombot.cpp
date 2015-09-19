#define _USE_MATH_DEFINES
#include "Girombot.h"

#include <math.h>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;


Girombot::Girombot()
{
	first = true;
	state = TROPPER;
}


Girombot::~Girombot()
{
}


void Girombot::process() {
	//TODO
	clean();

	if (first) {
		ms = duration_cast<milliseconds>(
			system_clock::now().time_since_epoch()
			).count();
		first = false;
	}

	double newTime = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
		).count();

	switch (state) {

		case TROPPER:
			if (checkIfCloseFromBorder())
				state = SNIPER;
			break;

		case SNIPER:
			GameObject* closestObject = closestObjectFromSelf();

			if (closestObject != nullptr) {
				Vector2 targetPos = Vector2(closestObject->posx, closestObject->posy);
				shootAtTarget(1, targetPos);
			}
			break;
	}

	sideThrustFront = -1;
	sideThrustBack = 1;
	stringstream sstm;
	sstm << myShip->velAng << " " << newTime - ms;
	gamestate->Log(sstm.str());
}

void Girombot::clean() {
	shoot = 0;
	pos = Vector2(myShip->posx, myShip->posy);
}

//Control
void Girombot::goToAngle(double angle) {
	double kd = 0.26;
	double kp = 1.41;
	double  r = M_PI * 30.0 / 180.0;

	double ang = M_PI * fmod(this->myShip->ang, 360.0) / 180;
	double w = M_PI * myShip->velAng / 180;
	double u = kp * (r - angle) - kd * w;

	//stringstream sstm;
	//sstm << myShip->posx << " " << myShip->posy;
	//sstm << 180 *angle / M_PI << " "  << 180 *w / M_PI;
	//gamestate->Log(sstm.str());
	//sstm.clear();
	//sstm << angle << " " << gamestate->tick << "  " << u;
	//gamestate->Log(sstm.str());


	//thrust = 0.2f;
	sideThrustFront = -u;
	sideThrustBack = +u;
	//shoot = 1;
}

//Actions
void Girombot::shootAtTarget(int intens, Vector2& target) {
	double angle = Vector2::angle(pos, target);
	if (angle < M_PI / 180 * 3.0) {
		shoot = intens;
	}

	else {
		goToAngle(angle);
	}
}


//Helper Functions
bool Girombot::checkIfCloseFromBorder() {
	double R = gamestate->arenaRadius;
	double diffX = 0 - myShip->posx;
	double diffY = 0 - myShip->posy;

	double theta = atan2(diffY, diffX);

	Vector2 intercep = Vector2(R * cos(theta), R * sin(theta));
	
	return Vector2::dist(pos, intercep) < 10.0;
}

GameObject* Girombot::closestObjectFromSelf() {
	GameObject *closestObject = nullptr;
	double minDist = 1 << 30;

	for (auto ship : gamestate->ships) {
		auto o = ship.second;
		Vector2 spos = Vector2(o->posx, o->posy);

		double distToObject = Vector2::dist(spos, pos);
		if (this->myShip != o && distToObject < minDist) {
			minDist = distToObject;
			closestObject = o;
		}
	}

	for (auto rock : gamestate->rocks) {
		auto o = rock.second;

		Vector2 spos = Vector2(o->posx, o->posy);

		double distToObject = Vector2::dist(spos, pos);
		if (distToObject < minDist) {
			minDist = distToObject;
			closestObject = o;
		}
	}

	for (auto laser : gamestate->lasers) {
		auto o = laser.second;

		Vector2 spos = Vector2(o->posx, o->posy);
		double distToObject = Vector2::dist(spos, pos);
		if (distToObject < minDist) {
			minDist = distToObject;
			closestObject = o;
		}
	}

	return closestObject;
}
