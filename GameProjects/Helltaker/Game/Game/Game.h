#pragma once

#include <Engine/Engine.h>
#include "Level/GameLevel.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();

	static Game& Get() { return *instance; }

	void NextLevel();

	void ReLevel();

	int index = 0;

private:
	bool showMenu = false;

	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

private:
	static Game* instance;
};