#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"

class DrawableActor;
class Start;
class Player;
class DemoLevel : public Level
{
	// RTTI 정의.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();

	// 업데이트 함수
	virtual void Update(float deltaTime) override;

	// 레벨 그리기 함수
	virtual void Draw() override;

	// 텍스트 파일 읽기
	void TextFileRead(const char* filename);

	// start 지점 설정 가능 여부 확인 함수
	bool CanStartPosition(const Vector2& position);

	// end 지점 설정 가능 여부 확인 함수
	bool CanEndPosition(const Vector2& position);

private:
	// 벽, 장애물 액터 배열
	std::vector<DrawableActor*> map;

	// Start 지점
	Start* start = nullptr;
	
	//End 지점
	Player* player = nullptr;

};