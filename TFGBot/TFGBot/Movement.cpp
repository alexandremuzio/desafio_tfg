#include "Movement.h"

#include "Ship.h"
#include "GameState.h"
#include "MoveAction.h"

Movement::Movement() {

}

Movement::~Movement() {

}

void Movement::Update() {
	
}

void Movement::setMyShip(Ship* ship) {
	Movement::myShip = ship;
}

void Movement::setGameState(GameState* gamestate) {
	Movement::gamestate = gamestate;
}

Ship* Movement::myShip = nullptr;
GameState* Movement::gamestate = nullptr;