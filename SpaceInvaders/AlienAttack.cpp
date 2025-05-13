#include "AlienAttack.h"

void AlienAttack::attack(Alien &a)
{
	if (!isActive)
	{
		float randomValue = rand() % 200 + 1;
		if (randomValue <= chancetoFire)
		{
			xPos = a.getXP();
			yPos = a.getYP() + 1;
			isActive = true;
		}
	}
}

void AlienAttack::update()
{
	if (isActive)
	{
		if (this->yPos < 29)
		{
			yPos++;
		}
		else
		{
			isActive = false;
		}
	}
}