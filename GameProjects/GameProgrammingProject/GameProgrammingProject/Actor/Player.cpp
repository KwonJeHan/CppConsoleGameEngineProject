#include "Player.h"
#include "Engine/Engine.h"
#include "Math/Vector2.h"

Player::Player(const char* image)
	: Super(image)
{
	position = Vector2(0, 0);
}

void Player::Update(float deltaTime)
{
	// �θ� �Լ� ȣ��
	Super::Update(deltaTime);

	// Ű �Է� ó��
	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		--newPosition.x;
		if (newPosition.x < 0)
		{
			newPosition.x = 0;
		}

		SetPosition(newPosition);
	}

	// Ű �Է� ó��
	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		++newPosition.x;
		//if (newPosition.x > 27)
		if (newPosition.x > Engine::Get().ScreenSize().x - width)
		{
			newPosition.x = Engine::Get().ScreenSize().x - width;
		}

		SetPosition(newPosition);
	}

	// Ű �Է� ó��
	if (Engine::Get().GetKeyDown(VK_UP))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		--newPosition.y;
		if (newPosition.y < 0)
		{
			newPosition.y = 0;
		}

		SetPosition(newPosition);
	}

	// Ű �Է� ó��
	if (Engine::Get().GetKeyDown(VK_DOWN))
	{
		// �� ��ġ ���
		Vector2 newPosition = position;
		++newPosition.y;
		if (newPosition.y > Engine::Get().ScreenSize().y - height)
		{
			newPosition.y = Engine::Get().ScreenSize().y - height;
		}

		SetPosition(newPosition);
	}
}
