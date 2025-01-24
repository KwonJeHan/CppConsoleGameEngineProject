#include "MainLevel.h"
#include "Game/Game.h"

MainLevel::MainLevel()
{
	mainItems.PushBack(new MainItem("Start  Game", []() { system("cls"); Game::Get().ReLevel(); }));
	mainItems.PushBack(new MainItem("Quit Game", []() { Game::Get().QuitGame(); }));
	length = mainItems.Size();
}

MainLevel::~MainLevel()
{
	for (auto* item : mainItems)
	{
		delete item;
	}
}

void MainLevel::Update(float deltaTime)
{
	if (Game::Get().GetKeyDown(VK_UP))
	{
		currentIndex = (currentIndex - 1 + length) % length;
	}
	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		currentIndex = (currentIndex + 1) % length;
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		mainItems[currentIndex]->onSelected();
	}
}

void MainLevel::Draw()
{
	Super::Draw();

	// 커서 감추기.
	Engine::Get().SetCursorType(CursorType::NoCursor);

	Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 20, (Engine::Get().ScreenSize().y / 2) + 2);
	//Engine::Get().SetCursorPosition(0, 0);

	SetColor(unselectedColor);
	Log("Helltaker\n\n");

	Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 19, (Engine::Get().ScreenSize().y / 2) + 4);
	for (int ix = 0; ix < length; ++ix)
	{
		SetColor(ix == currentIndex ? selectedColor : unselectedColor);
		Log("%s", mainItems[ix]->mainText);
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 20, (Engine::Get().ScreenSize().y / 2) + 5);
	}
}
