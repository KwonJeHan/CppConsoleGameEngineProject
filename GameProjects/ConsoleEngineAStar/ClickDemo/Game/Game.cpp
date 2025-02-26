#include "Game.h"


Game* Game::instance = nullptr;

Game::Game() : Engine()
{
	instance = this;
}

Game::~Game()
{
}

void Game::ReLevel()
{
	if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
	mainLevel = new DemoLevel;
}
