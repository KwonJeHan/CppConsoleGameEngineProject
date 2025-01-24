#include "Game.h"

#include "Level/MenuLevel.h"

Game* Game::instance = nullptr;

Game::Game()
	: Engine()
{
	instance = this;

	menuLevel = new MenuLevel();

}

Game::~Game()
{
	if (showMenu)
	{
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		delete mainLevel;
		mainLevel = nullptr;
	}

	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	system("cls");
	//Clear();
	showMenu = !showMenu;
	if (showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
	}
}

void Game::NextLevel()
{
	++index;
	if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
	mainLevel = new GameLevel;
}

void Game::ReLevel()
{
	if (mainLevel)
	{
		delete mainLevel;
		mainLevel = nullptr;
	}
	mainLevel = new GameLevel;
}
