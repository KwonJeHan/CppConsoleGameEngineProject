#include "DemoLevel.h"

#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"

DemoLevel::DemoLevel()
{

	AddActor(new Start());

	
	AddActor(new Player());
}

