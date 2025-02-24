#include "Engine/Engine.h"
#include "Level/DemoLevel.h"

int main()
{
	// 메모리 누수 확인
	CheckMemoryLeak();

	Engine engine;
	engine.LoadLevel(new DemoLevel());
	engine.Run();
}