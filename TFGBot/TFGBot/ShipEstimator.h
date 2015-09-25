#pragma once

#include "GameObjectEstimator.h"

class Ship;

class ShipEstimator : GameObjectEstimator {

private:

	static void EstimateVelAng(Ship*);
	static void EstimateAng(Ship*);

public:

	ShipEstimator();
	~ShipEstimator();

	static void Estimate(Ship*);
};

