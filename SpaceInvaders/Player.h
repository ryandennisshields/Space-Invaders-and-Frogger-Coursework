#pragma once
#include "GameObject.h"

class Player: public GameObject
{
public:
	Player(): GameObject(10) {};

	void update() override;
};

