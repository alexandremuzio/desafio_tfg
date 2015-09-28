#pragma once

#include "BotBase.h"
#include "MovementManager.h"
#include "Defense.h"
#include "Attack.h"

class PassedGSManager;
class BotBase;
class MovementManager;
class GameObject;

class ShipNorrisMA : public BotBase{

private:

	MovementManager* movManager;
	Defense* def;
	Attack* atk;

	void FirstTick();
	void UpdatePassedGS();
	void PrintPassedGS();
	void CheckDodge();
	bool NeedDodgeFrom( GameObject* go );

public:

	ShipNorrisMA();
	virtual ~ShipNorrisMA();
	virtual void Process();
};
