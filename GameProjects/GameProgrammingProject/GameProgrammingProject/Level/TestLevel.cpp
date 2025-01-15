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

	// ���� ó��
	if (deltaTime > 1.0f)
	{
		return;
	}

	// ESC Ű�� ����
	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		//Engine::Get().QuitGame();
		Game::Get().ToggleMenu();
	}
}
