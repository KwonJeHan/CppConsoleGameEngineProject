#pragma once

#include "Level/Level.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"
#include <vector>
#include <iostream>
#include <Windows.h>

class DemoLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();

	// �ʿ��� ����/��ǥ ��带 �˻��� �����ϴ� �Լ�.
	void FindStartAndGoalNode(std::vector<std::vector<int>>& grid, Node** outStartNode, Node** outGoalNode);
	

};