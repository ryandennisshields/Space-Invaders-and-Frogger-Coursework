#include "Obstacle.h"
int Obstacle::x;

void Obstacle::setPosition(int x, int y)
{
	this->xPos = x;
	this->yPos = y;
}

int Obstacle::getXPosition()
{
	return this->xPos;
}

int Obstacle::getYPosition()
{
	return this->yPos;
}

void Obstacle::setObstacle(int minX, int maxX, int xPos, int y, float speed, int direction)
{
	for (int i = minX; i < maxX; i++)
	{
		obstacleVector[i].setPosition(i + xPos, y);
		obstacleVector[i].setLaneProperties(speed, direction);
	}
}

void Obstacle::setLaneProperties(float newSpeed, int newDirection)
{
	speed = newSpeed;
	direction = newDirection;
}

void Obstacle::update() 
{
	for (auto& obstacle : obstacleVector) 
	{
		obstacle.xPos += obstacle.speed * obstacle.direction;
	}
}