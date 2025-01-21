#pragma once

#include <Actor/DrawableActor.h>


class Demon : public DrawableActor
{
	RTTI_DECLARATIONS(Demon, DrawableActor)

public:
	Demon(const Vector2& position);
};