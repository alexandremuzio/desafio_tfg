#pragma once

#include <vector>

class Ship;
class GameState;
class MoveAction;

using namespace std;

class Movement {

protected:

	static Ship* myShip;
	static GameState* gamestate;

public:

	Movement();
	~Movement();

	void Update();
	static void setMyShip(Ship*);
	static void setGameState(GameState*);
};