#pragma once
#include "GameObject.h"
#include <vector>
#include <array>

using namespace std;

class Obstacle : public GameObject
{
public:

	Obstacle() : isActive(true) {};

	Obstacle(const Obstacle& other)
		: isActive(other.isActive) {};

	~Obstacle() {};

	void setPosition(int x, int y);
	int getXPosition();
	int getYPosition();

	void setState(bool in) { isActive = in; };
	bool getState() { return isActive; }

	void setObstacle(int minX, int maxX, int xPos, int y, float speed, int direction);
	void setLaneProperties(float newSpeed, int newDirection);
	std::vector<Obstacle> obstacleVector;
	void update();

private:
	bool initialSetupComplete;
	static int x;
	bool isActive;
	float speed;
	int direction;
};