#include "Alien.h"

void Alien::setPosition(int x, int y)
{
	xPos = x;
	yPos = y;
}

void Alien::setActive(bool state) 
{
	this->m_isActive = state;
}

void Alien::draw()
{
	std::cout << "X";
}

void Alien::setSpeed(float x)
{
	this->m_speed = x;
}

void Alien::setDirection(float y)
{
	this->m_direction = y;
}

void Alien::update()
{
	xPos += m_speed * m_direction;
}

void Alien::moveDown() 
{
	yPos += 1;
}
