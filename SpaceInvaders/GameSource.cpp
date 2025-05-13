#include "GameSource.h"

float Alien::m_speed; // define static variable
float Alien::m_direction = 1;

extern int menuChoice; 

GameSource::GameSource() : m_player(new Player()), m_barriers(20), m_playerFrogger(new PlayerFrogger()) {}

GameSource::~GameSource()
{
	delete m_player;
	delete m_playerFrogger;
};

void GameSource::setPlayerPoisiton()
{
	if (gS == LEVEL1) 
	{
		m_player->setXPos(15);
		m_player->setYPos(PLAYER);
	}
	if (gS == FROGGER)
	{
		m_playerFrogger->setXPos(15);
		m_playerFrogger->setYPos(14);
	}
}

void GameSource::setAlienPositions()
{
	for (int i = 0; i < 20; i++)
	{
		m_aliens[i].setPosition(i*3, 1);
	}
}

void GameSource::setBarrierPositions()
{
	m_barriers.emplace_back(Barrier());

	for (int i = 0; i < 5; i++)
	{
		m_barriers[i].setPosition(i + 10, BARRIER);
	}
	for (int i = 5; i < 10; i++)
	{
		m_barriers[i].setPosition(i + 25, BARRIER);
	}
	for (int i = 10; i < 15; i++)
	{
		m_barriers[i].setPosition(i + 40, BARRIER);
	}
	for (int i = 15; i < 20; i++)
	{
		m_barriers[i].setPosition(i + 55, BARRIER);
	}
}

void GameSource::setCarPositions()
{
	m_obstacles.obstacleVector.emplace_back(Obstacle());
	m_obstacles.obstacleVector.resize(300);

#pragma region Placing Obstacles
	
	// Setup: (Min X + Previous Lane Max X, 
    //		  Max X + Previous Lane Max X,
    //		  X Position - Previous Lane Max X) 

	m_obstacles.setObstacle(0 + 0, 28 + 0, -0, 1, 0.08, 1); // 28

	m_obstacles.setObstacle(0 + 28, 27 + 28, -28, 2, 0.08, -1); // 55

	m_obstacles.setObstacle(0 + 55, 3 + 55, -55, 3, 0.08, 1);
	m_obstacles.setObstacle(6 + 55, 26 + 55, -55, 3, 0.08, 1); // 81

	m_obstacles.setObstacle(0 + 81, 4 + 81, -81, 4, 0.08, -1);
	m_obstacles.setObstacle(6 + 81, 17 + 81, -81, 4, 0.08, -1);
	m_obstacles.setObstacle(19 + 81, 23 + 81, -81, 4, 0.08, -1); // 104

	m_obstacles.setObstacle(8 + 104, 13 + 104, -104, 6, 0.16, 1); // 117

	m_obstacles.setObstacle(4 + 117, 8 + 117, -117, 7, 0.14, -1); 
	m_obstacles.setObstacle(16 + 117, 18 + 117, -117, 7, 0.14, -1); 
	m_obstacles.setObstacle(21 + 117, 25 + 117, -117, 7, 0.14, -1); // 142

	m_obstacles.setObstacle(2 + 142, 8 + 142, -142, 8, 0.14, 1);
	m_obstacles.setObstacle(20 + 142, 26 + 142, -142, 8, 0.14, 1); // 168

	m_obstacles.setObstacle(7 + 168, 9 + 168, -168, 9, 0.16, -1);
	m_obstacles.setObstacle(23 + 168, 25 + 168, -168, 9, 0.16, -1); // 193

	m_obstacles.setObstacle(13 + 193, 23 + 193, -193, 10, 0.12, 1); // 216

	m_obstacles.setObstacle(9 + 216, 16 + 216, -216, 11, 0.06, -1);
	m_obstacles.setObstacle(24 + 216, 27 + 216, -216, 11, 0.06, -1); // 243

	m_obstacles.setObstacle(17 + 243, 19 + 243, -243, 12, 0.04, 1); // 262

#pragma endregion
}

void GameSource::initaliseGame()
{
	m_gameWindow.setWindow(80, 30);
	createBuffers(80, 30);
	gS = STARTSCREEN;
}

void GameSource::setGame()
{
	if (!gameSetupComplete)
	{
		if (gS == LEVEL1)
		{
			m_gameWindow.setWindow(80, 30);
			createBuffers(80, 30);
			setPlayerPoisiton();
			setAlienPositions();
			setBarrierPositions();
		}
		else if (gS == FROGGER)
		{
			m_gameWindow.setWindow(30, 16);
			createBuffers(30, 16);
			setPlayerPoisiton();
			setCarPositions();
		}
		gameSetupComplete = true;
	}
}

void GameSource::processInput()
{
	if (gS == LEVEL1)
	{
		m_player->update();
		m_missile.firemissile(*m_player);
	}
	if (gS == FROGGER)
	{
		m_playerFrogger->update();
	}
}

void GameSource::updateGame()
{
	if (LEVEL1)
	{
		m_missile.update();
		for (int alien = 0; alien < sizeof(m_aliens) / sizeof(m_aliens[0]); alien++)
		{
			if (m_aliens[alien].m_isActive == true)
			{
				m_aliens[alien].update();
				m_alienAttack[alien].attack(m_aliens[alien]);
				m_alienAttack[alien].update();
			}
			else
			{
				m_alienAttack[alien].setActive(false);
			}
		}
		if (all_of(m_aliens, m_aliens + 20, [](const Alien& alien)
		{
				return !alien.m_isActive;
			})) 
		{
			win = true;
			gS = FINISH;
		}

		// Attempt here at making aliens move, but for some reason, moving the enemies down the screen never worked.
		// Only one alien would ever move down.
		
		//float x;
		//for (auto& alien : m_aliens) 
		//{
			//x = alien.getYP() > SPEED ? 1 : 0.5;
			//alien.setSpeed(x);
			//if (alien.getXP() == m_gameWindow.getWidth())
			//{
				//alien.setDirection(-1);
				//alien.moveDown();
			//}
		//}
	}
	if (gS == FROGGER)
	{
		m_obstacles.update();
		for (auto& car : m_obstacles.obstacleVector)
		{
			if (car.getXPos() >= m_gameWindow.getWidth())
				car.setXPos(0);
			else if (car.getXPosition() < 0)
				car.setXPos(m_gameWindow.getWidth());
		}

	}
}

void GameSource::checkCollision(int width, int height)
{
	if (gS == LEVEL1) 
	{
		int missileX = m_missile.getXPos();
		int missileY = m_missile.getYPos();

		for (auto& alien : m_aliens)
		{
			if (missileX == alien.getXP() && missileY == alien.getYP())
			{
				alien.setActive(false);
				m_missile.setActive(false);
			}
		}

		for (auto& barrier : m_barriers)
		{
			if (missileX == barrier.getXPos() && missileY == barrier.getYPos())
			{
				if (barrier.getState() == true)
				{
					m_missile.setActive(false);
				}
			}
		}

		for (auto& alienAttack : m_alienAttack)
		{
			int attackX = alienAttack.getXPos();
			int attackY = alienAttack.getYPos();

			if (attackX == m_player->getXPos() && attackY == m_player->getYPos())
			{
				gameOver = true;
				gS = FINISH;
			}

			for (auto& barrier : m_barriers)
			{
				if (attackX == barrier.getXPos() && attackY == barrier.getYPos())
				{
					if (barrier.getState() == true) 
					{
						barrier.setState(false);
						alienAttack.setActive(false);
					}
				}
			}
		}
	}
	if (gS == FROGGER) 
	{
		int playerX = m_playerFrogger->getXPos();
		int playerY = m_playerFrogger->getYPos();

		for (auto& car : m_obstacles.obstacleVector)
		{
			if (playerX == car.getXPos() && playerY == car.getYPos())
			{
				gameOver = true;
				gS = FINISH;
			}
		}
		if (playerY == 0) 
		{
			win = true;
			gS = FINISH;
		}
	}
}

void GameSource::setGameState(int x)
{
	gS = static_cast<gameState>(x);
}

void GameSource::setGamePositions(int width, int height)
{
	if (gS == LEVEL1)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				for (int aNo = 0; aNo < 20; aNo++)
				{
					if (m_aliens[aNo].m_isActive)
					{
						if ((m_aliens[aNo].getYP() == i) && (m_aliens[aNo].getXP() == j))
						{
							m_backBuffer.setChar(m_aliens[aNo].getXP(), m_aliens[aNo].getYP(), 'X');
						}
					}
				}
			}

			for (int j = 0; j < width; j++)
			{
				for (unsigned int bNo = 0; bNo < m_barriers.size(); bNo++)
				{
					if (m_barriers[bNo].getState() == true) 
					{
						if (m_barriers[bNo].getXPosition() == j)
						{
							m_backBuffer.setChar(m_barriers[bNo].getXPosition(), BARRIER, '=');
						}
					}
				}
			}

			if (m_missile.isActive)
			m_backBuffer.setChar(m_missile.getXPos(), m_missile.getYPos(), '|');

			for (int aNo = 0; aNo < 20; aNo++)
			{
				if (m_alienAttack[aNo].isActive)
				{
					m_backBuffer.setChar(m_alienAttack[aNo].getXPos(), m_alienAttack[aNo].getYPos(), '$');
				}
			}

			if (i == (PLAYER))
			{
				for (int j = 0; j < width; j++)
					if (m_player->getXPos() == j)
					{
						m_backBuffer.setChar(m_player->getXPos(), PLAYER, '^');
					}
			}

			else if (i == (GROUND))
			{
				for (int j = 0; j < width; j++)
					m_backBuffer.setChar(j, GROUND, '-');
			}
		}
	}
	if (gS == FROGGER)
	{
		for (int i = 0; i < height; i++)
		{
			#pragma region Obstacle Positions
			for (int j = 0; j < width; j++)
			{
				// Ranges: First value is equal to Distance, Second value is equal to Length)
				for (unsigned int bNo = 0; bNo < 28; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 1, '~');
					}
				}
				for (unsigned int bNo = 28; bNo < 55; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 2, '~');
					}
				}
				for (unsigned int bNo = 55; bNo < 81; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 3, '~');
					}
				}
				for (unsigned int bNo = 81; bNo < 104; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 4, '~');
					}
				}
				for (unsigned int bNo = 104; bNo < 117; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 6, '=');
					}
				}
				for (unsigned int bNo = 117; bNo < 142; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 7, '=');
					}
				}
				for (unsigned int bNo = 142; bNo < 168; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 8, '=');
					}
				}
				for (unsigned int bNo = 168; bNo < 193; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 9, '=');
					}
				}
				for (unsigned int bNo = 193; bNo < 216; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 10, '=');
					}
				}
				for (unsigned int bNo = 216; bNo < 243; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 11, '=');
					}
				}
				for (unsigned int bNo = 243; bNo < 262; bNo++) // unsigned explain
				{
					if (m_obstacles.obstacleVector[bNo].getXPosition() == j)
					{
						m_backBuffer.setChar(m_obstacles.obstacleVector[bNo].getXPosition(), 12, '=');
					}
				}
			}
			#pragma endregion

			for (int j = 0; j < width; j++)
			{
				m_backBuffer.setChar(m_playerFrogger->getXPos(), m_playerFrogger->getYPos(), '8');
			}

			for (int j = 0; j < width; j++)
				m_backBuffer.setChar(j, 15, '-');

		}
	}
};

void GameSource::drawGame(int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_gameWindow.setCursorPosition(j, i);
			std::cout << m_frontBuffer.getChar(j, i);
		}
	}
}

void GameSource::createBuffers(int width, int height)
{
	m_frontBuffer = ScreenBuffer(width, height);
	m_backBuffer = ScreenBuffer(width, height);
	m_resetBuffer = ScreenBuffer(width, height);

	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			m_resetBuffer.setChar(i, j, ' ');

	m_frontBuffer = m_resetBuffer;
	m_backBuffer = m_resetBuffer;

}
void GameSource::swapBuffers()
{
	m_frontBuffer = m_backBuffer;
	m_backBuffer = m_resetBuffer;
}

void GameSource::gameLoop()
{
	while (gS != gameState::EXIT)
	{
		switch (gS)
		{
		case STARTSCREEN:
			m_menu->run();
			this->setGameState(menuChoice);
			break;
		case LEVEL1:
			this->setGame();
			this->processInput();
			this->updateGame();
			this->checkCollision(m_gameWindow.getWidth(), m_gameWindow.getHeight());
			this->setGamePositions(m_gameWindow.getWidth(), m_gameWindow.getHeight());
			this->swapBuffers();
			this->drawGame(m_gameWindow.getWidth(), m_gameWindow.getHeight());
		case FROGGER:
			this->setGame();
			this->processInput();
			this->updateGame();
			this->checkCollision(m_gameWindow.getWidth(), m_gameWindow.getHeight());
			this->setGamePositions(m_gameWindow.getWidth(), m_gameWindow.getHeight());
			this->swapBuffers();
			this->drawGame(m_gameWindow.getWidth(), m_gameWindow.getHeight());
			break;
		case FINISH:
			if (gameOver == true) {
				system("cls");
				cout << "GAME OVER! Please quit the game!" << endl;
				gameOver = false;
			}
			if (win == true) {
				system("cls");
				cout << "YOU WIN! Please quit the game!" << endl;
				win = false;
			}
			break;
		}
	}
}
