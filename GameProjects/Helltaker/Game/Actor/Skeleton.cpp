#include "Skeleton.h"

Skeleton::Skeleton(const Vector2& position)
	: DrawableActor("S")//��
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::White;
}
