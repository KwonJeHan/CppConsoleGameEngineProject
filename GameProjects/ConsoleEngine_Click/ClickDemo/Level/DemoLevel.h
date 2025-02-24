#pragma once

#include "Level/Level.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"
#include <vector>
#include <iostream>
#include <Windows.h>

class DemoLevel : public Level
{
	// RTTI 정의.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();

	// 맵에서 시작/목표 노드를 검색해 생성하는 함수.
	void FindStartAndGoalNode(std::vector<std::vector<int>>& grid, Node** outStartNode, Node** outGoalNode);
	

};