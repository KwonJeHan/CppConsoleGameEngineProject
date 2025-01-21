#pragma once

#include <Actor/DrawableActor.h>


class Key : public DrawableActor
{
	RTTI_DECLARATIONS(Key, DrawableActor)

public:
	Key(const Vector2& position);
};