#include "Spike.h"

Spike::Spike(const Vector2& position)
	: DrawableActor("��")
{
	// ��ġ ����
	this->position = position;
	// ���� ����
	if (!active)
	{
		color = Color::White;
	}
	else
	{
		color = Color::Red;
	}
}
