#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "bot_interface.h"

using namespace std;

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

void GameState::Update()
{
	ReadData();
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
			
			if(ships[uid] == NULL)
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
			
			if(rocks[uid] == NULL)
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
			
			if(lasers[uid] == NULL)
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

void GameState::WriteData()
{
	std::cout << thrust << " " << sideThrustFront << " " << sideThrustBack << " " << shoot << endl;
}
