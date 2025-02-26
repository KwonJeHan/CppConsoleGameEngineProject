#include "Player.h"
#include "Engine/Engine.h"

Player::Player()
	: DrawableActor("e")
{
	color = Color::Green;
	position = Vector2(5, 5);
}

void Player::SetPath(const std::vector<Node*>& path)
{
    this->path = path;
    pathIndex = 0;
    moveTimer = 0.0f;
}

void Player::Draw()
{
	DrawableActor::Draw();
	for (int i = pathIndex; i < static_cast<int>(path.size()); i++)
	{
		Engine::Get().Draw(path[i]->GetPosition(), "*", Color::Green);
	}
}

void Player::Update(float deltaTime)
{
    DrawableActor::Update(deltaTime);

    if (Engine::Get().GetKeyDown(VK_RBUTTON))
    {
        SetPosition(Engine::Get().MousePosition());
    }

    moveTimer += deltaTime;
    if (moveTimer >= moveDelay && !path.empty() && pathIndex < static_cast<int>(path.size()))
    {
        Vector2 nextPos = path[pathIndex]->GetPosition();
        if (nextPos.x >= 0 && nextPos.y >= 0)
        {
            SetPosition(nextPos);
            Engine::Get().Draw(nextPos, "*");
        }
        pathIndex++;
        moveTimer = 0.0f;
    }
}