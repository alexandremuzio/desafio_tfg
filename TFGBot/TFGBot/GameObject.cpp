#include "GameObject.h"

GameObject::GameObject() {

}

GameObject::GameObject(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius) {
	uid = _uid;
	posx = _posx;
	posy = _posy;
	velx = _velx;
	vely = _vely;
	radius = _radius;
}

GameObject::~GameObject() {

}

void GameObject::CloneFrom(GameObject* go) {
	uid = go->uid;
	posx = go->posx;
	posy = go->posy;
	velx = go->velx;
	vely = go->vely;
	radius = go->radius;
}

void GameObject::UpdateBeforeBot() {
	
}