#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"

DemoLevel::DemoLevel()
{
    // 애니메이션
    // 콘솔 감추기.
    CONSOLE_CURSOR_INFO info = { };
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

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

    // 맵에서 시작 위치 목표 위치 검색
    Node* startNode = nullptr;
    Node* goalNode = nullptr;

    // 애니메이션
    // 맵에서 시작 위치와 목표위치 검색 후 노드 생성.
    FindStartAndGoalNode(grid, &startNode, &goalNode);

    // AStar 객체
    AStar aStar;

    // 경로 탐색
    std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

    // 결과 확인
    if (!path.empty())
    {
        std::cout << "경로를 찾았습니다. 탐색 경로 : \n";
        for (Node* node : path)
        {
            std::cout << "(" << node->position.x << "," << node->position.y << ") -> ";
        }
        std::cout << "도착\n";

        // 맵 출력
        std::cout << "경로를 맵에 표시한 결과 : \n";
        aStar.DisplayGridWithPath(grid, path);
    }
    else
    {
        std::cout << "경로를 찾지 못했습니다 \n";
    }

    // 목표 노드만 제거
    SafeDelete(goalNode);

    // 애니메이션
    // 콘솔 보이기.
    info.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // 콘솔 커서 이동 (기존 맵 출력에 방해되지 않도록).
    COORD position{ 0, 30 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
    std::cin.get();
}

void DemoLevel::FindStartAndGoalNode(std::vector<std::vector<int>>& grid, Node** outStartNode, Node** outGoalNode)
{
    bool hasInitialized = false;
    for (int x = 0; x < grid[0].size(); ++x)
    {
        if (*outStartNode != nullptr && *outGoalNode != nullptr)
        {
            hasInitialized = true;
            break;
        }

        for (int y = 0; y < grid.size(); ++y)
        {
            if (*outStartNode != nullptr && *outGoalNode != nullptr)
            {
                hasInitialized = true;
                break;
            }

            if (grid[y][x] == 2)
            {
                AddActor(new Start(Vector2(x, y)));
                *outStartNode = new Node(Vector2(x, y));
                continue;
            }

            if (grid[y][x] == 3)
            {
                AddActor(new Player(Vector2(x, y)));
                *outGoalNode = new Node(Vector2(x, y));
                continue;
            }
        }
    }
}
