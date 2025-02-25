#pragma once
#include "Actor/DrawableActor.h"
#include "Algorithm/Node.h"

class Start : public DrawableActor
{
public:
	Start();

	virtual void Update(float deltaTime) override;

private:
	Vector2 sPosition;
};