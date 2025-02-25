#pragma once

#include "Actor/DrawableActor.h"
#include "Math/Vector2.h"

class Start : public DrawableActor
{
public:
	Start();

	virtual void Update(float deltaTime) override;

	Vector2 GetPosition() const; // Add this method declaration
};