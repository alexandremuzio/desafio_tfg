#pragma once

#include "Ship.h"
#include "GameState.h"

class EstimatorManager {

private: 
	static GameState* gameState;
	static Ship* myShip;

public:
	EstimatorManager();
	static void Init(GameState* gameState, Ship* myShip);
	~EstimatorManager();

	static void Update();
};

