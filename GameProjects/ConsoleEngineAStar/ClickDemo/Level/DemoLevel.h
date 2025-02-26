#pragma once

#include "Level/Level.h"
#include "Algorithm/AStar.h"
#include "Actor/Player.h"
#include "Actor/Start.h"

class DemoLevel : public Level
{
    RTTI_DECLARATIONS(DemoLevel, Level)

public:
    DemoLevel();
    virtual ~DemoLevel();

    virtual void Update(float deltaTime) override;

    virtual void Draw() override;

private:
    void FindAndMovePath();
    //void MarkPath();
    //void PrintGrid();

    bool IsValidPosition(const Vector2& pos) const;

    AStar* astar;
    Start* start;
    Player* player;
    std::vector<Node*> currentPath;
    std::vector<std::vector<int>> grid;
};