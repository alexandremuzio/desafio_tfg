#include "GameConst.h"

GameConst::GameConst() {

}

GameConst::~GameConst() {

}

const float GameConst::shipMass = 1.0f;
const float GameConst::J = 2.0f;
const float GameConst::mainThrusterForce = 30.0f;
const float GameConst::sideThrustersForce = 15.0f;
const float GameConst::sideThrusterOffset = 2.0f;
const float GameConst::maxTorque = 2 * GameConst::sideThrusterOffset*GameConst::sideThrustersForce;
const float GameConst::maxVelAng = 9.32649f;
const float GameConst::maxAcAng = GameConst::maxTorque / GameConst::J;
const float GameConst::maxLinVel = 30.6f;
const int GameConst::nStoredGS = 3;
