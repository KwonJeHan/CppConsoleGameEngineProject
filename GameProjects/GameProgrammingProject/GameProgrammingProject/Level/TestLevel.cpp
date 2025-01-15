#include "TestLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Game/Game.h"

TestLevel::TestLevel()
{
	AddActor(new Player("<A>"));
}

TestLevel::~TestLevel()
{
}

void TestLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 예외 처리
	if (deltaTime > 1.0f)
	{
		return;
	}

	// ESC 키로 종료
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		Game::Get().ToggleMenu();
	}
}
