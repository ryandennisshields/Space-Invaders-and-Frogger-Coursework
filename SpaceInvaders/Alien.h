#pragma once
#include "GameObject.h"

class Alien:GameObject
{
public:
	Alien():m_isActive(true) {};
	~Alien() {};

	Alien(const Alien& other);

	void setPosition(int x, int y);
	void setSpeed(float x);
	void setDirection(float y);

	void draw() override;
	void setActive(bool state);

	int getXP() { return this->xPos; };
	int getYP() { return this->yPos; };
	bool m_isActive;

	void update();
	void moveDown();

private:
	static float m_speed;
	static float m_direction;
};

