#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

class GameObject
{
public:

	GameObject() {};
	GameObject(int x): xPos(x), yPos(0) {};
	~GameObject() {};

	virtual void update() {};
	virtual void draw() { std::cout << "called from based" << '\n'; };

	int getXPos() const { return this->xPos; };
	int getYPos() const { return this->yPos; };
#
	void setXPos(int x) { this->xPos = x; };
	void setYPos(int y) { this->yPos = y; };

protected:
	float xPos, yPos;
};