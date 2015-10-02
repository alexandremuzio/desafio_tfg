#include "MovementManager.h"

#include <stdexcept>

#include "Point.h"
#include "AlignAngMovement.h"
#include "AlignVelMovement.h"
#include "ApproachRectMovement.h"
#include "PassedGSManager.h"
#include "GameConst.h"
#include "DodgeLaserMovement.h"

MovementManager::MovementManager() {
	Movement::setMyShip(PassedGSManager::Get(0)->myShip);
	Movement::setGameState(PassedGSManager::Get(0));
	alignAngMov = nullptr;
	alignVelMov = nullptr;
	approachRectMov = nullptr;
	dodgeMov = nullptr;
	lastVel = Vector2(0.001f, 0.001f);
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
	if (dodgeMov != nullptr){
		if ( dodgeMov->Finish() )
			FinishDodge();
		else
			ma = ma + dodgeMov->Update();
	}	

	//ma.Print();

	return ma;
}

void MovementManager::StopAlignAng() {
	if (alignAngMov != nullptr)
		delete alignAngMov;
	alignAngMov = nullptr;
}

// ang in rad (belong between[-PI, PI]) and in trigonometric coordinates 
void MovementManager::AlignAng(float finalAng) {
	if (alignAngMov != nullptr)
		delete alignAngMov;
	alignAngMov = new AlignAngMovement(finalAng);
}

// ang in rad (belong between[-PI, PI]) an in triangle coordinates 
void MovementManager::AlignAng(float vx, float vy) {
	float angTrigCoord = MathUtils::GetAngFromVec2(vx, vy);
	AlignAng(angTrigCoord);
}

void MovementManager::AlignVel(float finalVelAng) {
	AlignVel(cos(finalVelAng), sin(finalVelAng));
}

void MovementManager::AlignVel(float vx, float vy, float desiredLinearVel) {
	this->desiredLinearVel = desiredLinearVel;
	lastVel = Vector2(vx, vy);
	float v = hypot(vx, vy);
	float k1 = desiredLinearVel / v;
	vx *= k1;
	vy *= k1;
	if (desiredLinearVel > GameConst::maxLinVel) {
		float k2 = (GameConst::maxLinVel) / desiredLinearVel;
		vx = k2*vx;
		vy = k2*vy;
	}

	/*if (alignVelMov != nullptr)
		delete alignVelMov;
		alignVelMov = new AlignVelMovement(vx, vy);*/

	if (alignVelMov != nullptr && alignVelMov->OneCycleExecuted()) {
		delete alignVelMov;
		alignVelMov = new AlignVelMovement(vx, vy);
	}
	if (alignVelMov == nullptr)
		alignVelMov = new AlignVelMovement(vx, vy);
}

void MovementManager::AlignVel(float vx, float vy) {
	lastVel = Vector2(vx, vy);
	float v = hypot(vx, vy);
	float k1 = desiredLinearVel / v;
	vx *= k1;
	vy *= k1;
	if (desiredLinearVel > GameConst::maxLinVel) {
		float k2 = (GameConst::maxLinVel) / desiredLinearVel;
		vx = k2*vx;
		vy = k2*vy;
	}

	/*if (alignVelMov != nullptr)
	delete alignVelMov;
	alignVelMov = new AlignVelMovement(vx, vy);*/

	if (alignVelMov != nullptr && alignVelMov->OneCycleExecuted()) {
		delete alignVelMov;
		alignVelMov = new AlignVelMovement(vx, vy);
	}
	if (alignVelMov == nullptr)
		alignVelMov = new AlignVelMovement(vx, vy);
}

void MovementManager::ApproachRect(Point* p, float ang) {
	
}

void MovementManager::ApproachRect(Point* p1, Point*p2) {
	
}

void MovementManager::Dodge(GameObject* go) {
	if (alignVelMov != nullptr) {
		delete alignVelMov;
		alignVelMov = nullptr;
	}
	dodgeMov = new DodgeLaserMovement(go);
}

void MovementManager::FinishDodge() {
	if (dodgeMov) {
		delete dodgeMov;
		dodgeMov = nullptr;
	}
	SetDesiredLinearVel(0.0f);
}

void MovementManager::SetDesiredLinearVel(float desiredVel) {
	this->desiredLinearVel = desiredVel;
	AlignVel(lastVel.x, lastVel.y);
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

bool MovementManager::Dodging() {
	return dodgeMov != nullptr;
}