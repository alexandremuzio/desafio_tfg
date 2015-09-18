#include "BotBase.h"

BotBase::BotBase()
{
	gamestate = NULL;
	myShip = NULL;
	thrust = 1.0f;
	sideThrustFront = 1.0f;
	sideThrustBack = 1.0f;
	shoot = 0;
}

BotBase::~BotBase()
{
	
}
	
void BotBase::Update()
{
	if(gamestate != NULL)
	{
		if(myShip != NULL)
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