#pragma once
#include <iostream>
#include <windows.h>

using namespace std;

class Window
{
public:	
	Window() {};

	void setWindow(int width, int height);
	void setCursorPosition(int x, int y);

	int getWidth() { return this->width; }

	int getHeight() { return this->height; }

private:
	int width, height;	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
};