#include "AlignVelMovement.h"

#include <sstream>
#include <vector>
#include <algorithm>

#include "Ship.h";
#include "MathUtils.h"
#include "GameState.h"

AlignVelMovement::AlignVelMovement(float vx, float vy) {
	desVel = Vector2(vx, vy);
	stage = 0;

	/*stringstream ss;
	ss << "init new AlignVelMovement";
	ss << "\t" << vxd << "(vxd)";
	ss << "\t" << vyd << "(vyd)";
	gamestate->Log(ss.str());*/
}

AlignVelMovement::~AlignVelMovement() {
	
}

MoveAction AlignVelMovement::Update() {
	if (stage == 0) {
		InitStages();
		Stage0Update();
		IncStage();
	}
	else if (stage == 1) {
		Stage1Update();
		IncStage();
	}

	return ma;
}

// For ascendent order v0 < v1 ?
bool comp(const pair<Vector2, float>& p0, const pair<Vector2, float>& p1) {
	return p0.second < p1.second;
}

void AlignVelMovement::InitStages() {
	float x1 = myShip->velx - desVel.x;
	float x2 = myShip->vely - desVel.y;
	Vector2 ac = Vector2(2.30*x1 - 3.14*x2, 3.14*x1 - 2.30*x2);
	float desAng = ac.Angle();

	vector< pair<Vector2, float> > v;
	v.push_back(pair<Vector2, float>(Vector2::UP, abs(Vector2::Angle(Vector2::UP, myShip->GetDirVec()))));
	v.push_back(pair<Vector2, float>(Vector2::UP_RIGHT, abs(Vector2::Angle(Vector2::UP_RIGHT, myShip->GetDirVec()))));
	v.push_back(pair<Vector2, float>(Vector2::RIGHT, abs(Vector2::Angle(Vector2::RIGHT, myShip->GetDirVec()))));
	v.push_back(pair<Vector2, float>(Vector2::RIGHT_DOWN, abs(Vector2::Angle(Vector2::RIGHT_DOWN, myShip->GetDirVec()))));
	v.push_back(pair<Vector2, float>(Vector2::DOWN, abs(Vector2::Angle(Vector2::DOWN, myShip->GetDirVec()))));
	v.push_back(pair<Vector2, float>(Vector2::DOWN_LEFT, abs(Vector2::Angle(Vector2::DOWN_LEFT, myShip->GetDirVec()))));
	v.push_back(pair<Vector2, float>(Vector2::LEFT, abs(Vector2::Angle(Vector2::LEFT, myShip->GetDirVec()))));
	v.push_back(pair<Vector2, float>(Vector2::LEFT_UP, abs(Vector2::Angle(Vector2::LEFT_UP, myShip->GetDirVec()))));
	sort(v.begin(), v.end(), comp);

	dir0 = v[0].first;
	dir1 = v[1].first;

	pair<float, float> ks = ac.Decompose(dir0, dir1);
	amp0 = ks.first;
	amp1 = ks.second;
}

void AlignVelMovement::IncStage() {
	stage++;
	stage %= nStages;
}

MoveAction AlignVelMovement::Stage0Update() {
	return MoveAction(dir0, amp0);
}

MoveAction AlignVelMovement::Stage1Update() {
	return MoveAction(dir1, amp1);
}

int AlignVelMovement::nStages = 2;