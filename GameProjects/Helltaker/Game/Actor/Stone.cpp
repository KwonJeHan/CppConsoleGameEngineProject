#include "Stone.h"

Stone::Stone(const Vector2& position)
	: DrawableActor("B")//��
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::White;
}
