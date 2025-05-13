#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "Window.h"
#include "Ground.h"
#include "Player.h"
#include "PlayerFrogger.h"
#include "Alien.h"
#include "AlienAttack.h"
#include "Barrier.h"
#include "Obstacle.h"
#include "Menu.h"
#include "Missile.h"
#include "ScreenBuffer.h"
#include <array>
#include <vector>

#define GROUND 29
#define PLAYER 28
#define BARRIER 22
#define SPEED 20

class GameSource
{
public:
	GameSource();
	~GameSource();

	void setGame();
	void setPlayerPoisiton();
	void setAlienPositions();
	void setBarrierPositions();
	void setCarPositions();
	void createBuffers(int width, int height);
	void initaliseGame();
	void processInput();
	void swapBuffers();
	void updateGame();
	void setGameState(int x);
	void setGamePositions(int width, int height);
	void checkCollision(int width, int height);
	void drawGame(int width, int height);
	void gameLoop();

private:
	bool m_runLoop = true;
	bool gameSetupComplete = false;
	bool gameOver = false;
	bool win = false;
	bool carPositions = true;
	Window m_gameWindow;
	Ground m_gameGround;

	std::unique_ptr<Menu> m_menu = std::make_unique<Menu>();
	
	Player* m_player;
	Missile m_missile;
	PlayerFrogger* m_playerFrogger;

	Alien m_aliens[20];
	AlienAttack m_alienAttack[20];

	ScreenBuffer m_frontBuffer;
	ScreenBuffer m_backBuffer;
	ScreenBuffer m_resetBuffer;
	std::vector<Barrier> m_barriers;
	Obstacle m_obstacles;

	enum gameState 
	{
		STARTSCREEN,
		LEVEL1,
		FROGGER,
		EXIT,
		FINISH
	};

	gameState gS;
};