#pragma once

#include <Actor/DrawableActor.h>


class Skeleton : public DrawableActor
{
	RTTI_DECLARATIONS(Skeleton, DrawableActor)

public:
	Skeleton(const Vector2& position);
};