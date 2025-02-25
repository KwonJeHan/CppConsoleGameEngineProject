#include "AStar.h"
#include "Node.h"

#include <iostream>
#include <Windows.h>

AStar::AStar()
{
}

AStar::~AStar()
{
    // 메모리 해제
    for (Node* node : openList)
    {
        SafeDelete(node);
    }

    openList.clear();

    for (Node* node : closedList)
    {
        SafeDelete(node);
    }

    closedList.clear();
}

// 애니메이션 grid const 삭제
std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, std::vector<std::vector<int>>& grid)
{
    // 시작 지점/목표 지점 저장
    this->startNode = startNode;
    this->goalNode = goalNode;

    // 시작 위치를 열린 리스트에 추가
    openList.emplace_back(startNode);

    // 상하좌우 및 대각선 이동 방향 및 비용 계산
    std::vector<Direction> directions =
    {
        // 하상우좌 이동
        { 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

        // 대각선 이동
        { 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f }
    };

    // 이웃 노드 탐색(열린 리스트가 비어 있지 않으면 반복)
    while (!openList.empty())
    {
        // 현재 열린 리스트에서 비용(fCost)이 가장 낮은 노드 검색
        // 최적화 가능(우선 순위 큐, 힙)
        Node* lowestNode = openList[0];
        for (Node* node : openList)
        {
            if (node->fCost < lowestNode->fCost)
            {
                lowestNode = node;
            }
        }

        // 비용이 가장 작은 노드를 현재 노드로 선택
        Node* currentNode = lowestNode;

        // 현재 노드가 목표 노드인지 확인
        if (IsDestination(currentNode))
        {
            // 목표 지점으로부터 역추적해서 경로를 생성 후 반환
            return ConstructPath(currentNode);
        }

        // 방문 처리를 위해 현재 노드를 열린 리스트에서 제거
        for (int ix = 0; ix < (int)openList.size(); ++ix)
        {
            // 두 노드의 위치를 기반으로 같은지 확인
            if (*openList[ix] == *currentNode)
            {
                openList.erase(openList.begin() + ix);
                break;
            }
        }

        // 방문 처리를 위해 닫힌 리스트에 추가
        // 이미 추가된 노드는 제외
        bool isNodeInList = false;
        for (Node* node : closedList)
        {
            // 위치 기반으로 비교
            if (*node == *currentNode)
            {
                isNodeInList = true;
                break;
            }
        }

        // 이미 있으면 무시
        if (isNodeInList)
        {
            continue;
        }
        
        // 없으면 닫힌 리스트에 추가
        closedList.emplace_back(currentNode);
        
        // 이웃 노드 방문 (하상우좌 .. 차례로 방문)
        for (const Direction& direction : directions)
        {
            // 다음에 이돌할 위치 확인
            int newX = currentNode->position.x + direction.x;
            int newY = currentNode->position.y + direction.y;
        
            // 그리드 벗어나면 무시
            if (!IsInRange(newX, newY, grid))
            {
                continue;
            }
        
            // 이동할 노드가 이동 가능한지 확인
            if (grid[newY][newX] == 1)
            {
                continue;
            }
        
            // 이미 방문했는지 확인
            if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
            {
                continue;
            }
        
            // 방문할 노드 생성 (비용 계산)
            Node* neighborNode = new Node(Vector2(newX, newY), currentNode);
            neighborNode->gCost = currentNode->gCost + direction.cost;
            neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
        
            // 열린 리스트에 추가
            // 이미 리스트에 있는지 확인
            Node* openListNode = nullptr;
            for (Node* node : openList)
            {
                if (*node == *neighborNode)
                {
                    openListNode = node;
                    break;
                }
            }
        
            // 이웃 노드가 리스트에 없으면 바로 추가
            // 리스트에 있으면 비용을 비교해 더 저렴하면 추가
            if (openListNode == nullptr
                || neighborNode->gCost < openListNode->gCost
                || neighborNode->fCost < openListNode->fCost)
            {
                // 애니메이션
                grid[newY][newX] = 5;
                openList.emplace_back(neighborNode);
            }
            else
            {
                // 리스트 추가 대상이 아니라면, 메모리 해제
                SafeDelete(neighborNode);
            }

            // 애니메이션
            DisplayGrid(grid);
            int delay = static_cast<int>(0.05f * 1000);
            Sleep(delay);
        }
    }

    // 탐색 실패
    // initialize_list (c++)
    //return {};
    return std::vector<Node*>();
}

void AStar::DisplayGridWithPath(
    std::vector<std::vector<int>>& grid, const std::vector<Node*>& path)
{
    static COORD position = { 0, 0 };
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, position);

    int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    int green = FOREGROUND_GREEN;

    // 구분을 위해 설정했던 데이터 초기화.
    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[0].size(); ++x)
        {
            int& value = grid[y][x];
            if (value == 2 || value == 3 || value == 5)
            {
                value = 0;
            }
        }
    }

    // 경로를 제외한 맵 출력.
    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[0].size(); ++x)
        {
            // 장애물.
            if (grid[y][x] == 1)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "1 ";
            }


            // 빈 공간.
            else if (grid[y][x] == 0)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "0 ";
            }
        }

        std::cout << "\n";
    }

    // 경로 출력.
    for (const Node* node : path)
    {
        // 경로는 '2'로 표시.
        COORD position{ static_cast<short>(node->position.x * 2), static_cast<short>(node->position.y) };
        SetConsoleCursorPosition(handle, position);
        SetConsoleTextAttribute(handle, green);

        std::cout << "* ";
        int delay = static_cast<int>(0.05f * 1000);
        Sleep(delay);
    }
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
    // 목표 노드로부터 부모 노드를 따라 역추적하면서 경로 설정
    std::vector<Node*> path;
    Node* currentNode = goalNode;
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parent;
    }

    // 시작 지점부터 목표 지점으로 향하도록 배열 뒤집기
    std::reverse(path.begin(), path.end());
    return path;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
    // 현재 노드에서 목표 노드까지의 차이 계산
    Vector2 diff = *currentNode - *goalNode;

    return std::sqrtf(diff.x * diff.x + diff.y * diff.y);
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
    // 벗어난 경우인지 확인
    if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
    {
        return false;
    }

    return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
    // 열린/닫힌 리스트에 이미 해당 위치가 있으면 방문한 것으로 판단
    for (int ix = 0; ix < (int)openList.size(); ++ix)
    {
        Node* node = openList[ix];
        if (node->position.x == x && node->position.y == y)
        {
            // 위치도 같고 비용이 더 크면 방문할 이유 없음
            if (gCost >= node->gCost)
            {
                return true;
            }

            // 새 노드의 비용이 작은 경우에는 기존 노드 제거
            openList.erase(openList.begin() + ix);
            SafeDelete(node);
        }
    }

    for (int ix = 0; ix < (int)closedList.size(); ++ix)
    {
        Node* node = closedList[ix];
        if (node->position.x == x && node->position.y == y)
        {
            // 위치도 같고 비용이 더 크면 방문할 이유 없음
            if (gCost >= node->gCost)
            {
                return true;
            }

            // 새 노드의 비용이 작은 경우에는 기존 노드 제거
            closedList.erase(closedList.begin() + ix);
            SafeDelete(node);
        }
    }

    // 리스트에 없으면 방문하지 않은 것으로 판단
    return false;
}

bool AStar::IsDestination(Node* node)
{
    return *node == *goalNode;
}


// 애니메이션
void AStar::DisplayGrid(std::vector<std::vector<int>>& grid)
{
    static COORD position = { 0, 0 };
    static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, position);

    int white = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    int green = FOREGROUND_GREEN;

    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[0].size(); ++x)
        {
            // 시작 위치.
            if (grid[y][x] == 2)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_RED);
                std::cout << "S ";
            }

            // 목표 위치.
            if (grid[y][x] == 3)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_RED);
                std::cout << "G ";
            }

            // 장애물.
            if (grid[y][x] == 1)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "1 ";
            }

            // 경로.
            else if (grid[y][x] == 5)
            {
                SetConsoleTextAttribute(handle, green);
                std::cout << "+ ";
            }

            // 빈 공간.
            else if (grid[y][x] == 0)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "0 ";
            }
        }

        std::cout << "\n";
    }
}
