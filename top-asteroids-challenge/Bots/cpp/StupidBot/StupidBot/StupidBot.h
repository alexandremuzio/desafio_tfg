#ifndef StupidBot_H
#define StupidBot_H

#include "BotBase.h"

class StupidBot : public BotBase
{
private:
	PassedGSManager* passedGSManager;

	void FirstTick();
	void UpdatePassedGS();
	void PrintPassedGS();

public:
	void SetPassedGSManager(PassedGSManager*);

	StupidBot();
	virtual ~StupidBot();
	virtual void Process();
};

#endif
