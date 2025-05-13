#pragma once
#include "GameObject.h"
#include "Alien.h"
#include <random>

class AlienAttack : public GameObject
{
public:
	AlienAttack() : isActive(false), chancetoFire(1) {}
	void attack(Alien& a);
	void update();
	void setActive(bool state) { this->isActive = state; }
	bool getState() { return this->isActive; }
	bool isActive;

	int chancetoFire;
};