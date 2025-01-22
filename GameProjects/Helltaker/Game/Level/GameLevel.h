#pragma once

#include <Level/Level.h>
#include <Math/Vector2.h>

// 소코반 게임 레벨.
class DrawableActor;
class Player;
class Stone;
class Skeleton;
class Target;
class Spike;
class Gate;
class Key;
class Demon;
class GameLevel : public Level
{
    RTTI_DECLARATIONS(GameLevel, Level)

public:
    GameLevel();

    // 업데이트 함수
    virtual void Update(float deltaTime) override;

    // 레벨의 그리기 함수
    virtual void Draw() override;

    // 플레이어가 이동이 가능한 지 확인하는 함수
    bool CanPlayerMove(const Vector2& position);

    // 스테이지 선택
    void SelectStage();

    // 텍스트 파일 읽기
    void TextFileRead(const char* filename);

    // 파일 인덱스
    int fileIndex = 0;

private:
    // 현재 스테이지를 클리어 했는지 확인하는 함수
    bool CheckStageClear();

    // 모든 스테이지를 클리어 했는지 확인하는 함수
    bool CheckGameClear();

    // 이동 횟수가 이동 가능 횟수를 넘어가서 게임 오버 됐는지 확인하는 함수
    bool CheckGameOver();

private:
    // 벽/땅 액터 배열.
    List<DrawableActor*> map;

    // 박스 액터
    List<Stone*> stones;

    // 타겟 액터
    List<Target*> targets;

    // 해골 액터
    List<Skeleton*> skeletons;

    // 가시 함정 액터
    List<Spike*> spikes;

    // 문 액터
    List<Gate*> gates;

    // 열쇠 액터
    List<Key*> keys;

    // 악마 액터
    Demon* demon = nullptr;

    // 플레이어 액터
    Player* player = nullptr;

    // 스테이지 클리어 변수
    bool isStageClear = false;

    // 게임 클리어 변수
    bool isGameClear = false;
    bool lastStage = false;

    // 게임 오버 변수
    bool isGameOver = false;

    // 이동 가능 횟수
    int moveLimit;

};