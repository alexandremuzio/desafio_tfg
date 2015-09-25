#include <iostream>
#include "bot_interface.h"

//Change to your bot's .h
#include "StupidBot.h"
#include "PassedGSManager.h"

using namespace std;

int main (int argc, char *argv[])
{	
	GameState * gamestate = new GameState();
	PassedGSManager * passedGSManager = new PassedGSManager();

	//Change to your bot's class name 
	StupidBot * bot = new StupidBot();
	bot->SetPassedGSManager(passedGSManager);
	
	bot->gamestate = gamestate;
	bot->myShip = gamestate->myShip;
	
	gamestate->Log("Loaded");
	
	while(bot->myShip != nullptr)
	{
		//gamestate->Update();
		gamestate->UpdateBeforeBot(passedGSManager);
		passedGSManager->Update(gamestate);
		bot->Update();
		gamestate->UpdateAfterBot(passedGSManager);
		//gamestate->WriteData();
	}
	
	delete gamestate;
	delete bot;
	
	return 0;
}