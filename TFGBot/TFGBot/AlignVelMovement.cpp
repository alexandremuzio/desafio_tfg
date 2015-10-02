#include "AlignVelMovement.h"

#include <sstream>
#include <vector>
#include <algorithm>

#include "Ship.h";
#include "MathUtils.h"
#include "GameState.h"

AlignVelMovement::AlignVelMovement() {
	desVel = Vector2();
}

AlignVelMovement::AlignVelMovement(float vx, float vy) {
	desVel = Vector2(vx, vy);
	stage = 0;
	OneCycleExecuted(false);

	/*stringstream ss;
	ss << "init new AlignVelMovement:"<< endl;
	ss << vx << "(vx desired)" << endl;
	ss << vy << "(vy desired)";
	gamestate->Log(ss.str());*/
}

AlignVelMovement::~AlignVelMovement() {
	
}

MoveAction AlignVelMovement::Update() {
	MoveAction ma;

	/*InitStages();
	ma = Stage0Update();*/

	/*stringstream ss;
	ss << "stage = " << stage << endl;
	gamestate->Log(ss.str());*/

	if (stage == 0) {
		InitStages();
		ma = Stage0Update();
		IncStage();
		
	}
	else if (stage == 1) {
		OneCycleExecuted(true);

		/*stringstream ss;
		ss << "call stage 1 ********************&&&"<< endl;
		gamestate->Log(ss.str());*/

		ma = Stage1Update();
		IncStage();
	}

	return ma;
}

// For ascendant order v0 < v1 ?
bool comp(const pair<Vector2, float>& p0, const pair<Vector2, float>& p1) {
	return p0.second < p1.second;
}

void AlignVelMovement::InitStages() {
	float k1 = 67.7651;
	float k2 = 10.6370;

	float x1 = myShip->velx - desVel.x;
	float x2 = myShip->estimatedAcX;
	float newAcx = myShip->estimatedAcX + gamestate->GetTimeStep()*(-k1*x1-k2*x2);

	float y1 = myShip->vely - desVel.y;
	float y2 = myShip->estimatedAcY;
	float newAcy = myShip->estimatedAcY + gamestate->GetTimeStep()*(-k1*y1 - k2*y2);

	Vector2 ac = Vector2(newAcx, newAcy);
	//ac.Print("new acceleration");

	float desAng = ac.Angle();

	pair<Vector2, Vector2> p = GetClosestVectors(ac);

	dir0 = p.first;
	dir1 = p.second;

	/*dir0.Print("dir0");
	dir1.Print("dir1");*/

	/*stringstream ss;
	ss << "amp0 = " << amp0 << endl;
	ss << "amp1 = " << amp1 << endl;
	gamestate->Log(ss.str());*/

	pair<float, float> ks = ac.Decompose(myShip->GetCorrectDir(dir0), myShip->GetCorrectDir(dir1));
	amp0 = ks.first;
	amp1 = ks.second;

	if (amp1 < 0.2f*amp0) {
		OneCycleExecuted(true);
	}
}

pair<Vector2, Vector2> AlignVelMovement::GetClosestVectors( const Vector2& acVec ) {
	vector< pair<Vector2, float> > v;
	v.push_back(pair<Vector2, float>(Vector2::UP, abs(Vector2::Angle(myShip->GetUpVec(), acVec))));
	v.push_back(pair<Vector2, float>(Vector2::UP_RIGHT, abs(Vector2::Angle(myShip->GetUpRightVec(), acVec))));
	v.push_back(pair<Vector2, float>(Vector2::RIGHT, abs(Vector2::Angle(myShip->GetRightVec(), acVec))));
	v.push_back(pair<Vector2, float>(Vector2::RIGHT_DOWN, abs(Vector2::Angle(myShip->GetRightDownVec(), acVec))));
	v.push_back(pair<Vector2, float>(Vector2::DOWN, abs(Vector2::Angle(myShip->GetDownVec(), acVec))));
	v.push_back(pair<Vector2, float>(Vector2::DOWN_LEFT, abs(Vector2::Angle(myShip->GetDownLeftVec(), acVec))));
	v.push_back(pair<Vector2, float>(Vector2::LEFT, abs(Vector2::Angle(myShip->GetLeftVec(), acVec))));
	v.push_back(pair<Vector2, float>(Vector2::LEFT_UP, abs(Vector2::Angle(myShip->GetLeftUpVec(), acVec))));
	sort(v.begin(), v.end(), comp);

	/*stringstream ss;
	ss << "Vector2::Angle(myShip->GetUpVec(), acVec) = " << Vector2::Angle(myShip->GetUpVec(), acVec) << endl;
	ss << "Vector2::Angle(myShip->GetUpRightVec(), acVec) = " << Vector2::Angle(myShip->GetUpRightVec(), acVec) << endl;
	ss << "Vector2::Angle(myShip->GetRightVec(), acVec)) = " << Vector2::Angle(myShip->GetRightVec(), acVec) << endl;
	ss << "Vector2::Angle(myShip->GetRightDownVec(), acVec) = " << Vector2::Angle(myShip->GetRightDownVec(), acVec) << endl;
	ss << "Vector2::Angle(myShip->GetDownVec(), acVec) = " << Vector2::Angle(myShip->GetDownVec(), acVec) << endl;
	ss << "Vector2::Angle(myShip->GetDownLeftVec(), acVec)) = " << Vector2::Angle(myShip->GetDownLeftVec(), acVec) << endl;
	ss << "Vector2::Angle(myShip->GetDownLeftVec(), acVec) = " << Vector2::Angle(myShip->GetDownLeftVec(), acVec) << endl;
	ss << "Vector2::Angle(myShip->GetLeftUpVec(), acVec) = " << Vector2::Angle(myShip->GetLeftUpVec(), acVec) << endl;
	gamestate->Log(ss.str());*/

	/*myShip->GetUpVec().Print("GetUpVec");
	myShip->GetUpRightVec().Print("GetUpRightVec");
	myShip->GetRightVec().Print("GetRightVec");
	myShip->GetRightDownVec().Print("GetRightDownVec");
	myShip->GetDownVec().Print("GetDownVec");
	myShip->GetDownLeftVec().Print("GetDownLeftVec");
	myShip->GetLeftVec().Print("GetLeftVec");
	myShip->GetLeftUpVec().Print("GetLeftUpVec");*/

	return pair<Vector2, Vector2>(v[0].first, v[1].first);
}

void AlignVelMovement::IncStage() {
	stage++;
	stage %= nStages;
}

MoveAction AlignVelMovement::Stage0Update() {
	stringstream ss;
	/*ss << amp0 << "(amp0-Stage0Update)" << endl;
	ss << amp1 << "(amp1-Stage0Update)" << endl;*/
	/*gamestate->Log(ss.str());*/

	return MoveAction(dir0, amp0);
}

MoveAction AlignVelMovement::Stage1Update() {
	return MoveAction(dir1, amp1);
}

int AlignVelMovement::nStages = 2;