#include <Windows.h>
#include "DemoLevel.h"
#include "Engine/Engine.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"

DemoLevel::DemoLevel()
{
	// 그리드 생성.
	// 0: 이동 가능.
	// 1: 이동 불가(장애물).
	// 2: 시작 위치.
	// 3: 목표 위치.
	std::vector<std::vector<int>> grid =
	{
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	};

	Start* start = new Start();
	AddActor(start);
	//AddActor(new Start());
	Node* startNode = nullptr;
	
	Player* player = new Player();
	AddActor(player);
	//AddActor(new Player());
	Node* goalNode = nullptr;

	if (Engine::Get().GetKeyDown(VK_RETURN))
	{
		bool hasInitialized = false;
		for (int x = 0; x < grid[0].size(); ++x)
		{
			if (startNode != nullptr && goalNode != nullptr)
			{
				hasInitialized = true;
				break;
			}

			for (int y = 0; y < grid.size(); ++y)
			{
				if (startNode != nullptr && goalNode != nullptr)
				{
					hasInitialized = true;
					break;
				}

				if (grid[y][x] == 2)
				{
					startNode = new Node((x, y));
					grid[y][x] = 0;
					continue;
				}

				if (grid[y][x] == 3)
				{
					goalNode = new Node((x, y));
					grid[y][x] = 0;
					continue;
				}
			}

			if (hasInitialized)
			{
				break;
			}
		}

		// 객체 생성.
		AStar aStar;

		// 경로 탐색.
		std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

		// 경로 탐색에 성공한 경우 관련 정보 출력.
		if (!path.empty())
		{
			std::cout << "경로를 찾았습니다. 최단 경로:\n";
			for (Node* node : path)
			{
				std::cout << "(" << node->position.x << ", " << node->position.y << ") -> ";
			}
			std::cout << "목표 도착\n";

			// 경로 탐색 결과 2차원 맵 출력.
			std::cout << "경로를 맵에 표시한 결과:\n";
			aStar.DisplayGridWithPath(grid, path);
		}

		// 경로 탐색에 실패.
		else
		{
			std::cout << "경로를 찾지 못했습니다.\n";
		}
	}

	// 메모리 해제.
	SafeDelete(goalNode);
}

