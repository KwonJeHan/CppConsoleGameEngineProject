#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"

DemoLevel::DemoLevel()
{
    // �ִϸ��̼�
    // �ܼ� ���߱�.
    CONSOLE_CURSOR_INFO info = { };
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // �׸��� ����.
    // 0: �̵� ����.
    // 1: �̵� �Ұ�(��ֹ�).
    // 2: ���� ��ġ.
    // 3: ��ǥ ��ġ.
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

    // �ʿ��� ���� ��ġ ��ǥ ��ġ �˻�
    Node* startNode = nullptr;
    Node* goalNode = nullptr;

    // �ִϸ��̼�
    // �ʿ��� ���� ��ġ�� ��ǥ��ġ �˻� �� ��� ����.
    FindStartAndGoalNode(grid, &startNode, &goalNode);

    // AStar ��ü
    AStar aStar;

    // ��� Ž��
    std::vector<Node*> path = aStar.FindPath(startNode, goalNode, grid);

    // ��� Ȯ��
    if (!path.empty())
    {
        std::cout << "��θ� ã�ҽ��ϴ�. Ž�� ��� : \n";
        for (Node* node : path)
        {
            std::cout << "(" << node->position.x << "," << node->position.y << ") -> ";
        }
        std::cout << "����\n";

        // �� ���
        std::cout << "��θ� �ʿ� ǥ���� ��� : \n";
        aStar.DisplayGridWithPath(grid, path);
    }
    else
    {
        std::cout << "��θ� ã�� ���߽��ϴ� \n";
    }

    // ��ǥ ��常 ����
    SafeDelete(goalNode);

    // �ִϸ��̼�
    // �ܼ� ���̱�.
    info.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

    // �ܼ� Ŀ�� �̵� (���� �� ��¿� ���ص��� �ʵ���).
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
