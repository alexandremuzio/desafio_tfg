#pragma once

#include "PassedGSManager.h"

class Estimator {

protected:
	static PassedGSManager* passedGSManager;

public:
	Estimator();
	~Estimator();

	static void setPassedGSManager(PassedGSManager*);
};

