#include "EstimatorManager.h"

#include <map>

#include "ShipEstimator.h"
#include "PassedGSManager.h"

using namespace std;

GameState* EstimatorManager::gameState;

Ship* EstimatorManager::myShip;

EstimatorManager::EstimatorManager() {
}

void EstimatorManager::Init(GameState* gs, Ship* ms) {
	gameState = gs;
	myShip = ms;
}

EstimatorManager::~EstimatorManager() {
}

void EstimatorManager::Update() {
	ShipEstimator::Estimate(myShip);
	/*for (map<int, Ship*>::iterator itr = PassedGSManager::Get(0)->ships.begin(); itr != PassedGSManager::Get(0)->ships.end(); itr++) {
		ShipEstimator::Estimate(itr->second);
		}*/
	// Call others estimators below
}