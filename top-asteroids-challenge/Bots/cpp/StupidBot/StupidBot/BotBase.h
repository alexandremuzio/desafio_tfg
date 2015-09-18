#ifndef BotBase_H
#define BotBase_H

#include "bot_interface.h"

class BotBase
{
protected:
	float thrust;
	float sideThrustFront;
	float sideThrustBack;
	int shoot;
	
public:
	GameState * gamestate;
	Ship * myShip;
	
	BotBase();
	virtual ~BotBase();
	
	void Update();
	virtual void Process();
};

#endif
