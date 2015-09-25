#include "Laser.h"

Laser::Laser() {

}

Laser::Laser(int _uid, float _posx, float _posy, float _velx, float _vely, float _radius, float _lifetime, int _owner) : GameObject(_uid, _posx, _posy, _velx, _vely, _radius) {
	lifetime = _lifetime;
	owner = _owner;
}

Laser::~Laser() {

}