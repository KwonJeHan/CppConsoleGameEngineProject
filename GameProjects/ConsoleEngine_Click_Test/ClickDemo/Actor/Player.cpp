#include "Player.h"
#include "Engine/Engine.h"

Player::Player(const Vector2& position)
	: DrawableActor("e")
{
	color = Color::Green;
	this->position = position;
}

void Player::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		position = Engine::Get().MousePosition();
	}
}