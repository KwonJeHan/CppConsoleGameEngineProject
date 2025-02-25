#pragma once
#include <vector>
#include "Actor/DrawableActor.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"

class Player : public DrawableActor
{
    RTTI_DECLARATIONS(Player, DrawableActor)

public:
    Player();

    virtual void Update(float deltaTime) override;
    void SetPath(const std::vector<Node*>& path);

private:
    std::vector<Node*> path;
    int pathIndex = 0;
    float moveTimer = 0.0f;
    const float moveDelay = 0.2f; // �̵� �ӵ� ����
};