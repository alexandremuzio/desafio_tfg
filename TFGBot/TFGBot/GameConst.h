#pragma once

class GameConst {

public:
	static const float shipMass;
	static const float J;
	static const float mainThrusterForce;
	static const float sideThrustersForce;
	static const float sideThrusterOffset;
	static const float maxTorque;
	static const float maxVelAng;
	static const float maxAcAng;
	static const float maxLinVel;
	static const int nStoredGS;

	GameConst();
	~GameConst();
};