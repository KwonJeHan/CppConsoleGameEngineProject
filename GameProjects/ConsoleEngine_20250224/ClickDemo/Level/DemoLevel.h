#pragma once

#include "Level/Level.h"


class Start;
class Player;
class DemoLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();

	

private:
	std::vector<std::vector<int>> grid;
	Start* start;
	Player* player;
};