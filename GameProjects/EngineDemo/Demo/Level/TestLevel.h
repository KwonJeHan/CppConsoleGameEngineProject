#pragma once

#include "Level\Level.h"

class TestLevel : public Level
{
public:
	TestLevel();
	~TestLevel();

	virtual void Update(float deltaTime);
};