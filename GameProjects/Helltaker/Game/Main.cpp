#include <iostream>
#include "Game/Game.h"
#include "Level/GameLevel.h"
#include "Level/MainLevel.h"

int main()
{
	// 메모리 누수 확인
	CheckMemoryLeak();

	Game game;
	game.LoadLevel(new MainLevel());
	game.Run();
}