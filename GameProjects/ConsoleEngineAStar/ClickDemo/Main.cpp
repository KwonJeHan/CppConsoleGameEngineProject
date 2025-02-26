#include "Engine/Engine.h"
#include "Level/DemoLevel.h"
#include "Core.h"

int main()
{
	CheckMemoryLeak();

	Engine engine;
	engine.LoadLevel(new DemoLevel());
	engine.Run();
}