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
	// 부모 함수 호출
	Super::Update(deltaTime);

	// 키 입력 처리
	if (Engine::Get().GetKeyDown(VK_LEFT))
	{
		// 새 위치 계산
		Vector2 newPosition = position;
		--newPosition.x;
		if (newPosition.x < 0)
		{
			newPosition.x = 0;
		}

		SetPosition(newPosition);
	}

	// 키 입력 처리
	if (Engine::Get().GetKeyDown(VK_RIGHT))
	{
		// 새 위치 계산
		Vector2 newPosition = position;
		++newPosition.x;
		//if (newPosition.x > 27)
		if (newPosition.x > Engine::Get().ScreenSize().x - width)
		{
			newPosition.x = Engine::Get().ScreenSize().x - width;
		}

		SetPosition(newPosition);
	}

	// 키 입력 처리
	if (Engine::Get().GetKeyDown(VK_UP))
	{
		// 새 위치 계산
		Vector2 newPosition = position;
		--newPosition.y;
		if (newPosition.y < 0)
		{
			newPosition.y = 0;
		}

		SetPosition(newPosition);
	}

	// 키 입력 처리
	if (Engine::Get().GetKeyDown(VK_DOWN))
	{
		// 새 위치 계산
		Vector2 newPosition = position;
		++newPosition.y;
		if (newPosition.y > Engine::Get().ScreenSize().y - height)
		{
			newPosition.y = Engine::Get().ScreenSize().y - height;
		}

		SetPosition(newPosition);
	}
}
