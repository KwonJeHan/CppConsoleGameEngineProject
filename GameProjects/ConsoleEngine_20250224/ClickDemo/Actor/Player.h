#pragma once

#include "Actor/DrawableActor.h"

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player();

	Vector2 GetPosition() const;
	virtual void Update(float deltaTime) override;
};