#include "Gate.h"

Gate::Gate(const Vector2& position)
	: DrawableActor("G")//��
{
	// ��ġ ����
	this->position = position;

	// ���� ����
	color = Color::Blue;
}
