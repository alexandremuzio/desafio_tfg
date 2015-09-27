#pragma once

#include <map>
#include <vector>
#include <sstream>

#include "Ship.h"
#include "MathUtils.h"

class PassedGSManager;
class Ship;
class Rock;
class Laser;

//using namespace std;

class GameState {

private:

	float thrust;
	float sideThrustFront;
	float sideThrustBack;
	int shoot;

	void ParseData(string toParse);

public:

	Ship * myShip;

	float tick;
	float timeStep;
	float arenaRadius;

	//Ships in the arena
	map<int, Ship*> ships;

	//Rocks in the arena
	map<int, Rock*> rocks;

	//Lasers in the arena
	map<int, Laser*> lasers;

	GameState();
	~GameState();
	void CloneFrom(GameState*);

	void ReadData();
	void UpdateBeforeBot();
	void UpdateAfterBot();
	void WriteData();

	float GetTick() const { return tick; }
	float GetArenaRadius() const { return arenaRadius; }
	float GetTimeStep() const { return timeStep; }

	float GetThrust() const { return thrust; }
	float GetSideThrustFront() const { return sideThrustFront; }
	float GetSideThrustBack() const { return sideThrustBack; }
	int GetShoot() const { return shoot; }

	void SetThrust(const float& _thrust) { thrust = _thrust; }
	void SetSideThrustFront(const float& _sideThrustFront) { sideThrustFront = _sideThrustFront; }
	void SetSideThrustBack(const float& _sideThrustBack) { sideThrustBack = _sideThrustBack; }
	void SetShoot(const int& _shoot) { shoot = _shoot; }

	void NormalizeAction();

	void Log(string message);
	void PrintAction();
	void PrintAction(string s);
};
