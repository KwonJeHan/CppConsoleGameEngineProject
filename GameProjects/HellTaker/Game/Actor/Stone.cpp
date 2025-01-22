#include "Stone.h"

Stone::Stone(const Vector2& position)
	: DrawableActor("B")//■
{
	// 위치 설정
	this->position = position;

	// 색상 설정
	color = Color::White;
}
