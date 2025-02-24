#include "Start.h"
#include "Engine/Engine.h"

Start::Start(const Vector2& position)
	: DrawableActor("s")
{
	color = Color::Red;
	this->position = position;
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		position = Engine::Get().MousePosition();
	}
}