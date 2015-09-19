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
	state = TROOPER;
}

Girombot::~Girombot()
{
}

//main loop
void Girombot::Process() {
	//TODO
	clean();

	//if (first) {
	//	ms = duration_cast<milliseconds>(
	//		system_clock::now().time_since_epoch()
	//		).count();
	//	first = false;
	//}

	//double newTime = duration_cast<milliseconds>(
	//	system_clock::now().time_since_epoch()
	//	).count();

	switch (state) {
		case TROOPER: {
			gamestate->Log("Trooper:");
			GameObject* closestObject = closestObjectFromSelf();
			if (closestObject == nullptr) {
				state = SNIPER;
				break;
			}
			Vector2 targetPos = Vector2(closestObject->posx, closestObject->posy);
			if (Vector2::dist(targetPos, pos) < 15) {
				state = DODGER;
				clean(); // stop thrusts
				break;
			}
			if (checkIfCloseFromBorder())
				state = SNIPER;

			//Moving center of arena
			else {
				gamestate->Log("	Leaving center of arena");
				double theta = atan2(0 - myShip->posx,
					0 - myShip->posy);
				thrustToAngle(0.5, theta);
			}
			break;
		}

		case SNIPER: {
			gamestate->Log("Sniper:");
			GameObject* closestObject = closestObjectFromSelf();
			if (closestObject == nullptr) {
				gamestate->Log("	No one to be seen");
				break;
			}
			Vector2 targetPos = Vector2(closestObject->posx, closestObject->posy);

			if (Vector2::dist(targetPos, pos) < 15) {
				state = DODGER;
			}

			else {
				//TODO change type of projectile logic
				gamestate->Log("	Trying to shoot someone");
				shootAtTarget(1, targetPos);
			}
			break;
		}

		case DODGER: {
			gamestate->Log("Dodger:");
			GameObject* closestObject = closestObjectFromSelf();

			if (closestObject == nullptr) {
				state = TROOPER;
				break;
			}

			Vector2 targetPos = Vector2(closestObject->posx, closestObject->posy);
			stringstream sstm;
			sstm << "	Distance: " << Vector2::dist(targetPos, pos);
			gamestate->Log(sstm.str());

			//dodge closing in object
			if (Vector2::dist(targetPos, pos) < 20) {
				gamestate->Log("	dodging someone");
				double escapeAngle = Vector2::angle(targetPos, pos);
				thrustToAngle(1, escapeAngle);
			}

			else if (!checkIfCloseFromBorder()) {
				state = TROOPER;
			}

			else {
				state = SNIPER;
			}
			break;
		}
	}

	//stringstream sstm;
	//sstm << myShip->velAng << " " << newTime - ms;
	//gamestate->Log(sstm.str());
}

void Girombot::clean() {
	shoot = 0;
	sideThrustBack = 0;
	sideThrustFront = 0;
	thrust = 0;
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


	sideThrustFront = -u;
	sideThrustBack = +u;
}

//Actions
void Girombot::shootAtTarget(int intens, Vector2& target) {
	double angle = Vector2::angle(pos, target);
	//angle threshold
	if (angle < M_PI / 180 * 3.0)
		shoot = intens;

	else
		goToAngle(angle);
}

//TODO ship speed must be taken in account
void Girombot::thrustToAngle(double u, double angle)
{
	double horizDirection = cos(angle) * u;
	double vertDirection = sin(angle) * u;

	sideThrustFront = horizDirection;
	sideThrustBack = -horizDirection;

	thrust = vertDirection;
}

//Helper Functions
bool Girombot::checkIfCloseFromBorder() {
	return Vector2::dist(pos, Vector2(0, 0)) < 30;
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
	
	//TODO - problem dodging his own laser
	//for (auto laser : gamestate->lasers) {
	//	auto o = laser.second;

	//	Vector2 spos = Vector2(o->posx, o->posy);
	//	double distToObject = Vector2::dist(spos, pos);
	//	if (distToObject < minDist) {
	//		minDist = distToObject;
	//		closestObject = o;
	//	}
	//}

	return closestObject;
}
