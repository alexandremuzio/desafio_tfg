#pragma once

#include "GameState.h"

class PassedGSManager {

public:
	static vector<GameState*> passedGS;

	PassedGSManager(GameState*);
	~PassedGSManager();
	
	static void Init(GameState*);
	static void Update();
	static GameState* Get(int);
	static void PrintPassedGS();
	static int nStored();
};