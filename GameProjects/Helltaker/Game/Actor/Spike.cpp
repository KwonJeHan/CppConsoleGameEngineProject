#include "Spike.h"

Spike::Spike(const Vector2& position)
	: DrawableActor("▦")//▦
{
	// 위치 설정
	this->position = position;
	
	// 색상 설정
	color = Color::Red;
}
