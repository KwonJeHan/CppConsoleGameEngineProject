#include "Demon.h"

Demon::Demon(const Vector2& position)
	: DrawableActor("D")
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::White;
}
