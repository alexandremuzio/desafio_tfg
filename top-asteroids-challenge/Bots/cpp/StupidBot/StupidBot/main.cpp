#include <iostream>
#include "bot_interface.h"

//Change to your bot's .h
#include "StupidBot.h"

using namespace std;

int main (int argc, char *argv[])
{	
	GameState * gamestate = new GameState();
	
	//Change to your bot's class name 
	StupidBot * bot = new StupidBot();
	
	bot->gamestate = gamestate;
	bot->myShip = gamestate->myShip;
	
	gamestate->Log("Loaded");
	
	while(bot->myShip != NULL)
	{
		gamestate->Update();
		bot->Update();
		gamestate->WriteData();
	}
	
	delete gamestate;
	delete bot;
	
	return 0;
}