#pragma once

#include "BotBase.h"

class PassedGSManager;
class BotBase;
class MovementManager;

class ShipNorrisMA : public BotBase{

private:

	MovementManager* movementManager;

	void FirstTick();
	void UpdatePassedGS();
	void PrintPassedGS();

public:

	ShipNorrisMA();
	virtual ~ShipNorrisMA();
	virtual void Process();
};
