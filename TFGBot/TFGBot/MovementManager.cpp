#include "MovementManager.h"

#include "Point.h"
#include "AlignAngMovement.h"
#include "AlignVelMovement.h"
#include "ApproachRectMovement.h"
#include "PassedGSManager.h"
#include "GameConst.h"

MovementManager::MovementManager() {
	Movement::setMyShip(PassedGSManager::Get(0)->myShip);
	Movement::setGameState(PassedGSManager::Get(0));
	alignAngMov = nullptr;
	alignVelMov = nullptr;
	approachRectMov = nullptr;
}

MovementManager::MovementManager(float desiredVel) : MovementManager() {
	SetDesiredLinearVel(desiredVel);
}

MovementManager::~MovementManager() {

}

MoveAction MovementManager::Update() {
	MoveAction ma;
	if (alignAngMov != nullptr)		ma = ma + alignAngMov->Update();
	if (alignVelMov != nullptr)		ma = ma + alignVelMov->Update();
	if (approachRectMov != nullptr)	ma = ma + approachRectMov->Update();

	//ma.Print();

	return ma;
}

// ang in rad (belong between[-PI, PI]) and in trigonometric coordinates 
void MovementManager::AlignAng(float finalAng) {
	alignAngMov = new AlignAngMovement(finalAng);
}

// ang in rad (belong between[-PI, PI]) an in triangle coordinates 
void MovementManager::AlignAng(float vx, float vy) {
	float angTrigCoord = MathUtils::GetAngFromVec2(vx, vy);
	AlignAng(angTrigCoord);
}

void MovementManager::AlignVel(float finalAngVel) {

}

void MovementManager::AlignVel(float vx, float vy) {
	float v = hypot(vx, vy);
	float k1 = desiredLinearVel / v;
	vx *= k1;
	vy *= k1;
	if (desiredLinearVel > GameConst::maxLinVel) {
		float k2 = (GameConst::maxLinVel) / desiredLinearVel;
		vx = k2*vx;
		vy = k2*vy;
	}
	alignVelMov = new AlignVelMovement(vx, vy);
}

void MovementManager::ApproachRect(Point* p, float ang) {
	
}

void MovementManager::ApproachRect(Point* p1, Point*p2) {
	
}

void MovementManager::SetDesiredLinearVel(float desiredVel) {
	this->desiredLinearVel = desiredVel;
}

bool MovementManager::AligningAng() {
	return alignAngMov != nullptr;
}

bool MovementManager::AligningVel() {
	return alignVelMov != nullptr;
}

bool MovementManager::ApproachingRect() {
	return approachRectMov != nullptr;
}