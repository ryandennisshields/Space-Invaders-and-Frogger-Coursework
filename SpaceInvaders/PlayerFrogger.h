#pragma once
#include "GameObject.h"

class PlayerFrogger : public GameObject
{
private:
	bool keyPressed = false;
public:
	PlayerFrogger() : GameObject(10) {};

	void update() override;
};