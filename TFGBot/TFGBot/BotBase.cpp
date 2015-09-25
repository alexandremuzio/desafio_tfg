#include "BotBase.h"
#include "GameState.h"

BotBase::BotBase()
{
	gamestate = nullptr;
	myShip = nullptr;
	thrust = 1.0f;
	sideThrustFront = 1.0f;
	sideThrustBack = 1.0f;
	shoot = 0;
}

BotBase::~BotBase(){
	
}
	
void BotBase::Update(){

	if(gamestate != nullptr)
	{
		if(myShip != nullptr)
		{
			Process();
		}
	
		gamestate->SetThrust(thrust);
		gamestate->SetSideThrustFront(sideThrustFront);
		gamestate->SetSideThrustBack(sideThrustBack);
		gamestate->SetShoot(shoot);
	}
}

void BotBase::Process()
{
	
}