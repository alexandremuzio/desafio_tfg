#include "EstimatorManager.h"

#include <map>

#include "ShipEstimator.h"
#include "PassedGSManager.h"

using namespace std;

EstimatorManager::EstimatorManager() {
}

EstimatorManager::~EstimatorManager() {
}

void EstimatorManager::Update() {
	for (map<int, Ship*>::iterator itr = PassedGSManager::Get(0)->ships.begin(); itr != PassedGSManager::Get(0)->ships.end(); itr++) {
		ShipEstimator::Estimate(itr->second);
	}
	// Call others estimators below
}