#include "Start.h"
#include "Engine/Engine.h"

Start::Start(const Vector2& position)
	: DrawableActor("s")
{
	// 위치 설정
	this->position = position;
	color = Color::Red;
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		position = Engine::Get().MousePosition();
	}

}