#pragma once

#include <Engine/Engine.h>
#include "Level/DemoLevel.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	static Game& Get() { return *instance; }

	void ReLevel();

private:
	static Game* instance;
};