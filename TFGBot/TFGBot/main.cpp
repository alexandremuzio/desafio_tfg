#include <iostream>

#include "ShipNorrisMA.h"
#include "PassedGSManager.h"
#include "GameState.h"
#include "Estimator.h"
#include "EstimatorManager.h"

using namespace std;

int main (int argc, char *argv[])
{	
	GameState * gamestate = new GameState();
	PassedGSManager::Init(gamestate);

	ShipNorrisMA * bot = new ShipNorrisMA();
	
	bot->gamestate = gamestate;
	bot->myShip = gamestate->myShip;
	
	gamestate->Log("Loaded");
	
	while(bot->myShip != nullptr)
	{
		gamestate->ReadData();

		stringstream ss;
		ss << "tick -> " << gamestate->GetTick();
		gamestate->Log(ss.str());

		gamestate->UpdateBeforeBot();
		EstimatorManager::Update();
		bot->Update();
		gamestate->UpdateAfterBot();
		PassedGSManager::Update(); // passedGS[0] always point to the current gamestate
		gamestate->WriteData();
	}
	
	delete gamestate;
	delete bot;
	
	return 0;
}