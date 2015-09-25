#include "Estimator.h"

Estimator::Estimator() {
}


Estimator::~Estimator() {
}

void Estimator::setPassedGSManager(PassedGSManager* pgsm) {
	passedGSManager = pgsm;
}

PassedGSManager* Estimator::passedGSManager = nullptr;