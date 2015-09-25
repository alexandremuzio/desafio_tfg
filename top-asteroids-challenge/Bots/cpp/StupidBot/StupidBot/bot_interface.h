#ifndef bot_interface_H
#define bot_interface_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>

# define rad2deg 57.295779
# define deg2rad  0.017453

using namespace std;

class PassedGSManager;

struct GameObject {
	int uid;
	float posx;
	float posy;
	float velx;
	float vely;
	float radius;

	GameObject();
	GameObject(int, float, float, float, float, float);
	~GameObject();
	void CloneFrom(GameObject*);
	void UpdateBeforeBot(PassedGSManager*);
};

struct Ship : public GameObject {
	float ang, estimatedAng;		// (rad)
	float velAng, estimatedVelAng;	// (rad / s)
	float acAng;					// Is updated after the action be defined (rad / s^2)
	float charge;					// Check if charge load has delay
	int score;

	Ship();
	Ship(int, float , float, float, float, float, float, float, float, int);
	~Ship();

	void CloneFrom(Ship*);
	void UpdateBeforeBot(PassedGSManager*);
	void UpdateAfterBot(PassedGSManager*);
};

struct Laser : public GameObject {
	float lifetime;
	int owner;

	Laser();
	Laser(int, float, float, float, float, float, float, int);
	~Laser();
};

struct Rock : public GameObject {
	Rock();
	Rock(int, float, float, float, float, float);
	~Rock();
};

class GameState {
	float thrust;
	float sideThrustFront;
	float sideThrustBack;
	int shoot;

	void ReadData();
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

	void UpdateBeforeBot(PassedGSManager*);
	void UpdateAfterBot(PassedGSManager*);
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

	void Log(string message);
};

#endif
