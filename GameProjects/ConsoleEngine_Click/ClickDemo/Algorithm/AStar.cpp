#include "AStar.h"
#include "Node.h"

#include <iostream>
#include <Windows.h>

AStar::AStar()
{
}

AStar::~AStar()
{
    // �޸� ����
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

// �ִϸ��̼� grid const ����
std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, std::vector<std::vector<int>>& grid)
{
    // ���� ����/��ǥ ���� ����
    this->startNode = startNode;
    this->goalNode = goalNode;

    // ���� ��ġ�� ���� ����Ʈ�� �߰�
    openList.emplace_back(startNode);

    // �����¿� �� �밢�� �̵� ���� �� ��� ���
    std::vector<Direction> directions =
    {
        // �ϻ���� �̵�
        { 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

        // �밢�� �̵�
        { 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f }
    };

    // �̿� ��� Ž��(���� ����Ʈ�� ��� ���� ������ �ݺ�)
    while (!openList.empty())
    {
        // ���� ���� ����Ʈ���� ���(fCost)�� ���� ���� ��� �˻�
        // ����ȭ ����(�켱 ���� ť, ��)
        Node* lowestNode = openList[0];
        for (Node* node : openList)
        {
            if (node->fCost < lowestNode->fCost)
            {
                lowestNode = node;
            }
        }

        // ����� ���� ���� ��带 ���� ���� ����
        Node* currentNode = lowestNode;

        // ���� ��尡 ��ǥ ������� Ȯ��
        if (IsDestination(currentNode))
        {
            // ��ǥ �������κ��� �������ؼ� ��θ� ���� �� ��ȯ
            return ConstructPath(currentNode);
        }

        // �湮 ó���� ���� ���� ��带 ���� ����Ʈ���� ����
        for (int ix = 0; ix < (int)openList.size(); ++ix)
        {
            // �� ����� ��ġ�� ������� ������ Ȯ��
            if (*openList[ix] == *currentNode)
            {
                openList.erase(openList.begin() + ix);
                break;
            }
        }

        // �湮 ó���� ���� ���� ����Ʈ�� �߰�
        // �̹� �߰��� ���� ����
        bool isNodeInList = false;
        for (Node* node : closedList)
        {
            // ��ġ ������� ��
            if (*node == *currentNode)
            {
                isNodeInList = true;
                break;
            }
        }

        // �̹� ������ ����
        if (isNodeInList)
        {
            continue;
        }
        
        // ������ ���� ����Ʈ�� �߰�
        closedList.emplace_back(currentNode);
        
        // �̿� ��� �湮 (�ϻ���� .. ���ʷ� �湮)
        for (const Direction& direction : directions)
        {
            // ������ �̵��� ��ġ Ȯ��
            int newX = currentNode->position.x + direction.x;
            int newY = currentNode->position.y + direction.y;
        
            // �׸��� ����� ����
            if (!IsInRange(newX, newY, grid))
            {
                continue;
            }
        
            // �̵��� ��尡 �̵� �������� Ȯ��
            if (grid[newY][newX] == 1)
            {
                continue;
            }
        
            // �̹� �湮�ߴ��� Ȯ��
            if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
            {
                continue;
            }
        
            // �湮�� ��� ���� (��� ���)
            Node* neighborNode = new Node(Vector2(newX, newY), currentNode);
            neighborNode->gCost = currentNode->gCost + direction.cost;
            neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
            neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;
        
            // ���� ����Ʈ�� �߰�
            // �̹� ����Ʈ�� �ִ��� Ȯ��
            Node* openListNode = nullptr;
            for (Node* node : openList)
            {
                if (*node == *neighborNode)
                {
                    openListNode = node;
                    break;
                }
            }
        
            // �̿� ��尡 ����Ʈ�� ������ �ٷ� �߰�
            // ����Ʈ�� ������ ����� ���� �� �����ϸ� �߰�
            if (openListNode == nullptr
                || neighborNode->gCost < openListNode->gCost
                || neighborNode->fCost < openListNode->fCost)
            {
                // �ִϸ��̼�
                grid[newY][newX] = 5;
                openList.emplace_back(neighborNode);
            }
            else
            {
                // ����Ʈ �߰� ����� �ƴ϶��, �޸� ����
                SafeDelete(neighborNode);
            }

            // �ִϸ��̼�
            DisplayGrid(grid);
            int delay = static_cast<int>(0.05f * 1000);
            Sleep(delay);
        }
    }

    // Ž�� ����
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

    // ������ ���� �����ߴ� ������ �ʱ�ȭ.
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

    // ��θ� ������ �� ���.
    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[0].size(); ++x)
        {
            // ��ֹ�.
            if (grid[y][x] == 1)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "1 ";
            }


            // �� ����.
            else if (grid[y][x] == 0)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "0 ";
            }
        }

        std::cout << "\n";
    }

    // ��� ���.
    for (const Node* node : path)
    {
        // ��δ� '2'�� ǥ��.
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
    // ��ǥ ���κ��� �θ� ��带 ���� �������ϸ鼭 ��� ����
    std::vector<Node*> path;
    Node* currentNode = goalNode;
    while (currentNode != nullptr)
    {
        path.emplace_back(currentNode);
        currentNode = currentNode->parent;
    }

    // ���� �������� ��ǥ �������� ���ϵ��� �迭 ������
    std::reverse(path.begin(), path.end());
    return path;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
    // ���� ��忡�� ��ǥ �������� ���� ���
    Vector2 diff = *currentNode - *goalNode;

    return std::sqrtf(diff.x * diff.x + diff.y * diff.y);
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
    // ��� ������� Ȯ��
    if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
    {
        return false;
    }

    return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
    // ����/���� ����Ʈ�� �̹� �ش� ��ġ�� ������ �湮�� ������ �Ǵ�
    for (int ix = 0; ix < (int)openList.size(); ++ix)
    {
        Node* node = openList[ix];
        if (node->position.x == x && node->position.y == y)
        {
            // ��ġ�� ���� ����� �� ũ�� �湮�� ���� ����
            if (gCost >= node->gCost)
            {
                return true;
            }

            // �� ����� ����� ���� ��쿡�� ���� ��� ����
            openList.erase(openList.begin() + ix);
            SafeDelete(node);
        }
    }

    for (int ix = 0; ix < (int)closedList.size(); ++ix)
    {
        Node* node = closedList[ix];
        if (node->position.x == x && node->position.y == y)
        {
            // ��ġ�� ���� ����� �� ũ�� �湮�� ���� ����
            if (gCost >= node->gCost)
            {
                return true;
            }

            // �� ����� ����� ���� ��쿡�� ���� ��� ����
            closedList.erase(closedList.begin() + ix);
            SafeDelete(node);
        }
    }

    // ����Ʈ�� ������ �湮���� ���� ������ �Ǵ�
    return false;
}

bool AStar::IsDestination(Node* node)
{
    return *node == *goalNode;
}


// �ִϸ��̼�
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
            // ���� ��ġ.
            if (grid[y][x] == 2)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_RED);
                std::cout << "S ";
            }

            // ��ǥ ��ġ.
            if (grid[y][x] == 3)
            {
                SetConsoleTextAttribute(handle, FOREGROUND_RED);
                std::cout << "G ";
            }

            // ��ֹ�.
            if (grid[y][x] == 1)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "1 ";
            }

            // ���.
            else if (grid[y][x] == 5)
            {
                SetConsoleTextAttribute(handle, green);
                std::cout << "+ ";
            }

            // �� ����.
            else if (grid[y][x] == 0)
            {
                SetConsoleTextAttribute(handle, white);
                std::cout << "0 ";
            }
        }

        std::cout << "\n";
    }
}
