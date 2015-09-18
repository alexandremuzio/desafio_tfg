#ifndef bot_interface_H
#define bot_interface_H
#include <map>

using namespace std;

struct GameObject
{	
	int uid;
	float posx;
	float posy;
	float velx;
	float vely;
	float radius;
	
	GameObject();
	
	GameObject(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius)
	{
		uid = _uid;
		posx = _posx;
		posy = _posy;
		velx = _velx;
		vely = _vely;
		radius = _radius;
	} 
	~GameObject(){};
};

struct Ship : public GameObject
{	
	float ang;
	float velAng;
	float charge;
	int score;
	
	Ship();
	
	Ship(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius, float _ang, float _velAng, float _charge, int _score) : GameObject(_uid, _posx, _posy, _velx, _vely, _radius)
	{
		ang = _ang;
		velAng = _velAng;
		charge = _charge;
		score = _score;
	} 
	~Ship(){};
};

struct Laser : public GameObject
{
	float lifetime;
	int owner;
	 
	Laser();
	
	Laser(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius, float _lifetime, int _owner) : GameObject(_uid, _posx, _posy, _velx, _vely, _radius)
	{
		lifetime = _lifetime;
		owner = _owner;
	} 
	~Laser(){};
	 
};

struct Rock : public GameObject 
{
	Rock();
	
	Rock(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius) : GameObject(_uid, _posx, _posy, _velx, _vely, _radius)
	{ };
	~Rock(){};
};

class GameState
{	
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
	map<int,Ship*> ships;
	
	//Rocks in the arena
	map<int,Rock*> rocks;
	
	//Lasers in the arena
	map<int,Laser*> lasers;

	GameState();
	~GameState();
	
	void Update();
	void WriteData();
	
	float GetTick() const { return tick; }
	float GetArenaRadius() const { return arenaRadius; }
	float GetTimeStep() const { return timeStep; }
	
	float GetThrust() const {return thrust;}
	float GetSideThrustFront() const {return sideThrustFront;}
	float GetSideThrustBack() const {return sideThrustBack;}
	int GetShoot() const {return shoot; }
	
	void SetThrust(const float& _thrust) {thrust = _thrust;}
	void SetSideThrustFront(const float& _sideThrustFront) {sideThrustFront = _sideThrustFront;}
	void SetSideThrustBack(const float& _sideThrustBack) {sideThrustBack = _sideThrustBack;}
	void SetShoot(const int& _shoot) {shoot = _shoot;}
	
	void Log(string message);
};

#endif
