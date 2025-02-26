#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Algorithm/AStar.h"
#include "Algorithm/Node.h"
#include "Engine/Engine.h"
#include <iostream>


DemoLevel::DemoLevel()
    : start(nullptr), player(nullptr), astar(new AStar()), grid(50, std::vector<int>(50, 0))
{
    start = new Start();
    player = new Player();

    AddActor(start);
    AddActor(player);
}

DemoLevel::~DemoLevel()
{
	// 메모리 릭 방지
    SafeDelete(astar);
}

void DemoLevel::Update(float deltaTime)
{
    Super::Update(deltaTime);

    if (Engine::Get().GetKeyDown(VK_ESCAPE))
    {
        Engine::Get().QuitGame();
    }

    if (Engine::Get().GetKeyDown(VK_RETURN))
    {
        FindAndMovePath();
    }

	/*if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		currentPath.clear();
		for (auto& row : grid)
		{
			for (int& cell : row)
			{
				cell = 0;
			}
		}
	}*/
}

void DemoLevel::Draw()
{
    start->Draw();
    player->Draw();

    //player->SetPath(currentPath);
    //MarkPath();
    //PrintGrid();
}

void DemoLevel::FindAndMovePath()
{
    Vector2 startPos = start->Position();
    Vector2 goalPos = player->Position();

    if (!IsValidPosition(startPos) || !IsValidPosition(goalPos))
    {
        std::cout << "Grid를 벗어난 start/goal 위치입니다.\n";
        return;
    }


    Node* startNode = new Node(startPos);
    Node* goalNode = new Node(goalPos);
    

    currentPath = astar->FindPath(startNode, goalNode, grid);

    if (currentPath.empty())
    {
        std::cout << "유효한 path가 없습니다.\n";
        return;
    }

    player->SetPath(currentPath);
    //MarkPath();
    //PrintGrid();
    
	// 메모리 릭 방지
	SafeDelete(goalNode);
}

//void DemoLevel::MarkPath()
//{
//    for (Node* node : currentPath)
//    {
//        Vector2 pos = node->GetPosition();
//        if (IsValidPosition(pos))
//        {
//            grid[pos.y][pos.x] = 2;
//            Engine::Get().Draw(pos, "*", Color::Green);
//        }
//    }
//}

//void DemoLevel::PrintGrid()
//{
//    for (const auto& row : grid)
//    {
//        for (int cell : row)
//        {
//            if (cell == 2)
//            {
//                std::cout << "* ";   
//            }
//            else
//            {
//                std::cout << "0 ";
//            }
//        }
//        std::cout << "\n";
//    }
//	std::cout << "\n";
//}

bool DemoLevel::IsValidPosition(const Vector2& pos) const
{
    return pos.x >= 0 && pos.x < grid[0].size() && pos.y >= 0 && pos.y < grid.size();
}