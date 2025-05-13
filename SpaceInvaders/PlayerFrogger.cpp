#include "PlayerFrogger.h"


void PlayerFrogger::update()
{
	if (GetKeyState('A') & 0x8000)
	{
		if (xPos > 0 && !keyPressed)
		{
			xPos--;
			keyPressed = true;
		}
	}
	else if (GetKeyState('D') & 0x8000)
	{
		if (xPos < 29 && !keyPressed)
		{
			xPos++;
			keyPressed = true;
		}
	}
	else if (GetKeyState('S') & 0x8000)
	{
		if (yPos < 14 && !keyPressed)
		{
			yPos++;
			keyPressed = true;
		}
	}
	else if (GetKeyState('W') & 0x8000)
	{
		if (yPos > 0 && !keyPressed)
		{
			yPos--;
			keyPressed = true;
		}
	}
	else 
	{
		keyPressed = false;
	}
}