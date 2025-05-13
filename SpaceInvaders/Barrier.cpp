#include "Barrier.h"
int Barrier::x; // extra copy?

void Barrier::setPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
}

int Barrier::getXPosition()
{
	return this->xPos;
}

int Barrier::getYPosition()
{
	return this->yPos;
}
