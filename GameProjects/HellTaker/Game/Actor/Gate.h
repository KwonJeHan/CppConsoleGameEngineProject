#pragma once

#include <Actor/DrawableActor.h>


class Gate : public DrawableActor
{
	RTTI_DECLARATIONS(Gate, DrawableActor)

public:
	Gate(const Vector2& position);
};