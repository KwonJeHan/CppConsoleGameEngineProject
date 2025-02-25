#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Algorithm/AStar.h"
#include "Algorithm/Node.h"
#include "Engine/Engine.h"
#include <iostream>

DemoLevel::DemoLevel()
    : start(nullptr), player(nullptr), astar(new AStar()), grid(10, std::vector<int>(10, 0)), startNode(nullptr)
{
    start = new Start();
    player = new Player();
    startNode = new Node(start->Position());

    AddActor(start);
    AddActor(player);
}

DemoLevel::~DemoLevel()
{
    //delete astar;
    //delete startNode;
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
}

void DemoLevel::FindAndMovePath()
{
    startNode->position = start->Position(); // 최신 위치 반영
    Vector2 goalPos = player->Position();

    if (!IsValidPosition(startNode->position) || !IsValidPosition(goalPos))
    {
        std::cout << "올바르지 않은 start/goal 위치입니다.";
        return;
    }

    Node goalNode(goalPos);

    currentPath = astar->FindPath(startNode, &goalNode, grid);

    if (currentPath.empty())
    {
        std::cout << "유효한 path가 없습니다.";
        return;
    }

    player->SetPath(currentPath);
    MarkPath();
    PrintGrid();
}

void DemoLevel::MarkPath()
{
    for (Node* node : currentPath)
    {
        Vector2 pos = node->GetPosition();
        if (IsValidPosition(pos))
        {
            grid[pos.y][pos.x] = 2;
            Engine::Get().Draw(pos, "*");
        }
    }
}

void DemoLevel::PrintGrid()
{
    for (const auto& row : grid)
    {
        for (int cell : row)
        {
            if (cell == 2)
                std::cout << "* ";
            else
                std::cout << "0 ";
        }
        std::cout << std::endl;
    }
}

bool DemoLevel::IsValidPosition(const Vector2& pos) const
{
    return pos.x >= 0 && pos.x < grid[0].size() && pos.y >= 0 && pos.y < grid.size();
}