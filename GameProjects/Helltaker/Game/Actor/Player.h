#pragma once

#include <Actor/DrawableActor.h>

// 게임 레벨 전방 선언
class GameLevel;
class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(const Vector2& position, GameLevel* level);

	virtual void Update(float deltaTime) override;

	// 이동 횟수
	int moveCount = 0;

	// 소지한 열쇠 개수
	int hasKey = 0;

private:
	// 게임 레벨을 참조하는 변수
	GameLevel* refLevel = nullptr;
};