#include "Player.h"


void Player::update()
{
	if (GetKeyState('A') & 0x8000)
	{
		if (xPos > 0)
			xPos--;
	}
	else if (GetKeyState('D') & 0x8000)
	{
		if (xPos < 79)
			xPos++;
	}
}

