#pragma once

#include <Actor/DrawableActor.h>

class Spike : public DrawableActor
{
	RTTI_DECLARATIONS(Spike, DrawableActor)

public:
	Spike(const Vector2& position);
};