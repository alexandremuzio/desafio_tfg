#include "bot_interface.h"
#include "PassedGSManager.h"
#include "GameConst.h"

using namespace std;

// GameObject struct implementation
// ########################################################################################################

GameObject::GameObject() {

}

GameObject::GameObject(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius) {
	uid = _uid;
	posx = _posx;
	posy = _posy;
	velx = _velx;
	vely = _vely;
	radius = _radius;
}

GameObject::~GameObject() {

}
	
void GameObject::CloneFrom(GameObject* go) {
	uid = go->uid;
	posx = go->posx;
	posy = go->posy;
	velx = go->velx;
	vely = go->vely;
	radius = go->radius;
}

void GameObject::UpdateBeforeBot(PassedGSManager* passedGSManager) {
	// Estimate parameters
}

// --------------------------------------------------------------------------------------------------------
// End GameObject struct implementation


// Ship struct implementation
// ########################################################################################################
Ship::Ship() {

}

Ship::Ship(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius, float _ang, float _velAng, float _charge, int _score) : GameObject(_uid, _posx, _posy, _velx, _vely, _radius) {
	ang = _ang;
	velAng = _velAng;
	charge = _charge;
	score = _score;
}

Ship::~Ship() {

};

void Ship::CloneFrom(Ship* ship) {
	GameObject::CloneFrom(ship);
	ang = ship->ang;
	velAng = ship->velAng;
	charge = ship->charge;
	score = ship->score;
	estimatedAng = ship->estimatedAng;
	estimatedVelAng = ship->estimatedVelAng;
	acAng = ship->acAng;
}

void Ship::UpdateBeforeBot(PassedGSManager* passedGSManager) {
	GameObject::UpdateBeforeBot(passedGSManager);
	ang *= deg2rad;
	velAng *= deg2rad;

	estimatedVelAng = velAng;
	for (int i = passedGSManager->nStored() - 1; i >= 1; --i)
		estimatedVelAng += passedGSManager->Get(i)->myShip->acAng*passedGSManager->Get(i)->timeStep;

	estimatedAng = ang + velAng*passedGSManager->Get(0)->timeStep;	// Idealy timeStep must be estimatedNextTimeStep if physics do not process in constant step.
																	// I think that for guarantee a good visibility while watching the game, 
																	// the physics step must be not constant, but it remains not know => send an email
	for (int i = passedGSManager->nStored() - 2; i >= 1; --i)
		estimatedAng += passedGSManager->Get(i)->myShip->estimatedVelAng*passedGSManager->Get(i)->timeStep;
}

void Ship::UpdateAfterBot(PassedGSManager* passedGSManager) {
	//acAng = 1 / Constants::Instance()->J*(2 * passedGSManager->Get(0)->GetSideThrustFront() - 2 * passedGSManager->Get(0)->GetSideThrustBack());
}
// --------------------------------------------------------------------------------------------------------
// End Ship struct implementation

// Laser struct implementation
// ########################################################################################################
Laser::Laser() {

}

Laser::Laser(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius, float _lifetime, int _owner) : GameObject(_uid, _posx, _posy, _velx, _vely, _radius) {
	lifetime = _lifetime;
	owner = _owner;
}

Laser::~Laser() {

}
// --------------------------------------------------------------------------------------------------------
// End Laser struct implementation

// Rock struct implementation
// ########################################################################################################
Rock::Rock() {

}

Rock::Rock(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius) : GameObject(_uid, _posx, _posy, _velx, _vely, _radius) {

}

Rock::~Rock() {

}
// --------------------------------------------------------------------------------------------------------
// End Rock struct implementation

GameState::GameState()
{
	thrust = 1.0f;
	sideThrustFront = 1.0f;
	sideThrustBack = 1.0f;
	shoot = true;
	myShip = new Ship(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0);
	ships.clear();
	rocks.clear();
	lasers.clear();
}

GameState::~GameState()
{
	for(map<int, Ship*>::iterator itr = ships.begin(); itr != ships.end(); itr++)
    {
        delete itr->second;
    }
    
    for(map<int, Rock*>::iterator itr = rocks.begin(); itr != rocks.end(); itr++)
    {
        delete itr->second;
    }
    
    for(map<int, Laser*>::iterator itr = lasers.begin(); itr != lasers.end(); itr++)
    {
       delete itr->second;
    }
}

void GameState::CloneFrom(GameState* gs) {
	myShip->CloneFrom(gs->myShip);
	// Implement others clones here
}

void GameState::UpdateBeforeBot(PassedGSManager* passedGSManager) {
	ReadData();
	myShip->UpdateBeforeBot(passedGSManager);
}

void GameState::ReadData()
{ 
	string data;
	std::getline(std::cin, data);

	
	ParseData(data);
}

void GameState::ParseData(string toParse)
{
	vector<int> shipIds;
	vector<int> rockIds;
	vector<int> laserIds;
	
	while(toParse.size() > 0)
	{
		string item;
		size_t delim = toParse.find('|');
		if(delim != std::string::npos)
			item = toParse.substr(0, delim + 1);
		else
			item = toParse;	
			
		toParse.erase(0,item.size());
		
		stringstream ssr(item);
		
		string type;
		ssr >> type;
		
		if(type.compare("uid") == 0)
		{
			int uid;
			ssr >> uid;
			myShip->uid = uid;
			ships[uid] = myShip;			
		}
		else if(type.compare("timestep") == 0)
		{
			ssr >> timeStep;
		}
		else if(type.compare("tick") == 0)
		{
			ssr >> tick;
		}
		else if(type.compare("arenaRadius") == 0)
		{
			ssr >> arenaRadius;
		}
		else if(type.compare("ship") == 0)
		{
			int uid;
			float posx;
			float posy;
			float velx;
			float vely;
			float radius;
			float ang;
			float velAng;
			float charge;
			int score;
			
			ssr >> uid;
			ssr >> posx;
			ssr >> posy;
			ssr >> velx;
			ssr >> vely;
			ssr >> radius;
			ssr >> ang;
			ssr >> velAng;
			ssr >> charge;
			ssr >> score;
			
			shipIds.push_back(uid);
			
			if(ships[uid] == nullptr)
			{
				Ship * newShip = new Ship(uid, posx, posy, velx, vely, radius, ang, velAng, charge, score);
				ships[uid] = newShip;
			}
			else 
			{
				ships[uid]->uid = uid;       
				ships[uid]->posx = posx;
				ships[uid]->posy = posy;
				ships[uid]->velx = velx;
				ships[uid]->vely = vely;
				ships[uid]->radius = radius;
				ships[uid]->ang = ang;
				ships[uid]->velAng = velAng;
				ships[uid]->charge = charge;
				ships[uid]->score = score;
			}
			
		}
		else if(type.compare("rock") == 0)
		{
			int uid;
			float posx;
			float posy;
			float velx;
			float vely;
			float radius;
			
			ssr >> uid;
			ssr >> posx;
			ssr >> posy;
			ssr >> velx;
			ssr >> vely;
			ssr >> radius;
			
			rockIds.push_back(uid);
			
			if(rocks[uid] == nullptr)
			{
				Rock * newRock = new Rock(uid, posx, posy, velx, vely, radius);
				rocks[uid] = newRock;
			}
			else 
			{
				rocks[uid]->uid = uid;       
				rocks[uid]->posx = posx;
				rocks[uid]->posy = posy;
				rocks[uid]->velx = velx;
				rocks[uid]->vely = vely;
				rocks[uid]->radius = radius;
			}
		}
		else if(type.compare("laser") == 0)
		{
			int uid;
			float posx;
			float posy;
			float velx;
			float vely;
			float radius;
			float lifetime;
			int owner;
			
			ssr >> uid;
			ssr >> posx;
			ssr >> posy;
			ssr >> velx;
			ssr >> vely;
			ssr >> radius;
			ssr >> lifetime;
			ssr >> owner;
			
			laserIds.push_back(uid);
			
			if(lasers[uid] == nullptr)
			{
				Laser * newLaser = new Laser(uid, posx, posy, velx, vely, radius, lifetime, owner);
				lasers[newLaser->uid] = newLaser;
			}
			else 
			{
				lasers[uid]->uid = uid;       
				lasers[uid]->posx = posx;
				lasers[uid]->posy = posy;
				lasers[uid]->velx = velx;
				lasers[uid]->vely = vely;
				lasers[uid]->radius = radius;
				lasers[uid]->lifetime = lifetime;
				lasers[uid]->owner = owner;
			}	
		}
	}
	
	for(map<int, Ship*>::iterator itr = ships.begin(); itr != ships.end();)
    {
    	bool found = false;
    	
        for(int i = 0; i < shipIds.size(); ++i)
        {
        	if(itr->first == shipIds[i])
        	{
        		found = true;
        	}
        }
        
        if(!found)
        {
        	delete itr->second;
        	ships.erase(itr++);
        }
        else
        {
        	itr++;
        }
    }

    for(map<int, Rock*>::iterator itr = rocks.begin(); itr != rocks.end();)
    {
       bool found = false;
    	
        for(int i = 0; i < rockIds.size(); ++i)
        {
        	if(itr->first == rockIds[i])
        	{
        		found = true;
        	}
        }
        
        if(!found)
        {
        	delete itr->second;
        	rocks.erase(itr++);
        }
        else
        {
        	itr++;
        }
    }
    
    for(map<int, Laser*>::iterator itr = lasers.begin(); itr != lasers.end();)
    {
       bool found = false;
    	
        for(int i = 0; i < laserIds.size(); ++i)
        {
        	if(itr->first ==laserIds[i])
        	{
        		found = true;
        	}
        }
        
        if(!found)
        {
        	delete itr->second;
        	lasers.erase(itr++);
        }
        else
        {
        	itr++;
        }
    } 
    
}

void GameState::Log(string message)
{
	std::cerr << message << endl;
}

void GameState::UpdateAfterBot(PassedGSManager* passedGSManager) {
	myShip->UpdateAfterBot(passedGSManager);
	WriteData();
}

void GameState::WriteData()
{
	std::cout << thrust << " " << sideThrustFront << " " << sideThrustBack << " " << shoot << endl;
}
