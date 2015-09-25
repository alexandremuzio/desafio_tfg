#pragma once

class GameObject;

class GameObjectEstimator {

public:

	GameObjectEstimator();
	~GameObjectEstimator();

	static void Estimate(GameObject*);
};

