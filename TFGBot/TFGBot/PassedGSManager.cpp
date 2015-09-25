#include "PassedGSManager.h"

#include "GameConst.h"

PassedGSManager::PassedGSManager(GameState* gs) {

}

PassedGSManager::~PassedGSManager() {

}

void PassedGSManager::Init(GameState* gs) {
	passedGS.resize(GameConst::nStoredGS);
	for (int i = 0; i < passedGS.size(); ++i)
		passedGS[i] = nullptr;
	passedGS[0] = gs;
}

void PassedGSManager::Update() {
	if (passedGS[passedGS.size() - 1] != nullptr)
		delete passedGS[passedGS.size() - 1];

	for (int i = passedGS.size() - 1; i > 1; --i)
		passedGS[i] = passedGS[i - 1];

	passedGS[1] = new GameState();
	passedGS[1]->CloneFrom(passedGS[0]);

	//PrintPassedGS();
}

GameState* PassedGSManager::Get(int i) {
	return passedGS[i];
}

void PassedGSManager::PrintPassedGS() {
	stringstream ss;
	ss << "tick: " << Get(0)->tick;
	for (int i = 0; i < passedGS.size(); ++i)
		if (Get(i) != nullptr)
			ss << " | " << "vely(" << i << ") = " << Get(i)->myShip->vely;
	Get(0)->Log(ss.str());
}

int PassedGSManager::nStored() {
	return passedGS.size();
}

vector<GameState*> PassedGSManager::passedGS = vector<GameState*>();