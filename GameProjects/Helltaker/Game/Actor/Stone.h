#pragma once

#include <Actor/DrawableActor.h>


class Stone : public DrawableActor
{
	RTTI_DECLARATIONS(Stone, DrawableActor)

public:
	Stone(const Vector2& position);
};