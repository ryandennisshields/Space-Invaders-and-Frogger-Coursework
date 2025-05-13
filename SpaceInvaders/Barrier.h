#pragma once
#include "GameObject.h"

class Barrier : public GameObject
{
public:

	Barrier() : isActive(true) {};
	
	Barrier(const Barrier& other) 
		: isActive(other.isActive){};
	
	~Barrier() {};

	void setPosition(int x, int y);
	int getXPosition();
	int getYPosition();

	void setState(bool in) { isActive = in; };
	bool getState() { return isActive; }

private:
	static int x;
	bool isActive;
};

