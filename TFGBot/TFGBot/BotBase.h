#pragma once

class Ship;
class GameState;

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