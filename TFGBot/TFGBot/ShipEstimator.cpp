#include "ShipEstimator.h"

#include "GameConst.h"
#include "Ship.h"
#include "PassedGSManager.h"

ShipEstimator::ShipEstimator() : GameObjectEstimator(){

}

ShipEstimator::~ShipEstimator(){
	
}

void ShipEstimator::Estimate(Ship* ship) {
	EstimateVelAng(ship);
	EstimateAng(ship);
}

void ShipEstimator::EstimateVelAng(Ship* ship) {
	ship->estimatedVelAng = ship->velAng;
	for (int i = PassedGSManager::nStored() - 1; i >= 1; --i) {
		if (PassedGSManager::Get(i) != nullptr) {
			// O acAng não existe para outras naves

			ship->estimatedVelAng += (PassedGSManager::Get(i)->myShip->acAng)*(PassedGSManager::Get(i)->GetTimeStep());
			/*stringstream ss;
			GameState* gs = PassedGSManager::Get(0);
			ss << i << "(i)";
			ss << "\t\t" << (PassedGSManager::Get(i)->GetTick()) << "(tick)";
			ss << "\t\t" << (PassedGSManager::Get(i)->myShip->acAng) << "(inc acAng)";
			ss << "\t\t" << (PassedGSManager::Get(i)->GetTimeStep()) << "(inc timeStep)";
			gs->Log(ss.str());*/
		}
	}
	ship->estimatedVelAng = MathUtils::Limit(ship->estimatedVelAng, -GameConst::maxVelAng, GameConst::maxVelAng);
}

void ShipEstimator::EstimateAng(Ship* ship) {
	ship->estimatedAng = ship->ang + ship->velAng*PassedGSManager::Get(0)->GetTimeStep();
	// Idealy timeStep must be estimatedNextTimeStep if physics do not process in constant step.
	// I think that for guarantee a good visibility while watching the game, 
	// the physics step must be not constant, but it remains not know => send an email
	// Log 20150920023222 say that physics do not process in constant step

	for (int i = PassedGSManager::nStored() - 2; i >= 1; --i) {
		if (PassedGSManager::Get(i) != nullptr) {
			ship->estimatedAng += PassedGSManager::Get(i)->myShip->estimatedVelAng*PassedGSManager::Get(i)->GetTimeStep();
			/*stringstream ss;
			GameState* gs = PassedGSManager::Get(0);
			ss << i << "(i)";
			ss << "\t\t" << (PassedGSManager::Get(i)->GetTick()) << "(tick)";
			ss << "\t\t" << (PassedGSManager::Get(i)->myShip->estimatedVelAng) << "(inc estimatedVelAng)";
			ss << "\t\t" << (PassedGSManager::Get(i)->GetTimeStep()) << "(inc timeStep)";
			gs->Log(ss.str());*/
		}
	}
}

