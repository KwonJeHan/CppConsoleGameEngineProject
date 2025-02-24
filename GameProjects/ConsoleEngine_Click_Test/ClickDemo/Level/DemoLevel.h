#pragma once

#include "Level/Level.h"
#include "Math/Vector2.h"

class DrawableActor;
class Start;
class Player;
class DemoLevel : public Level
{
	// RTTI ����.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel();

	// ������Ʈ �Լ�
	virtual void Update(float deltaTime) override;

	// ���� �׸��� �Լ�
	virtual void Draw() override;

	// �ؽ�Ʈ ���� �б�
	void TextFileRead(const char* filename);

	// start ���� ���� ���� ���� Ȯ�� �Լ�
	bool CanStartPosition(const Vector2& position);

	// end ���� ���� ���� ���� Ȯ�� �Լ�
	bool CanEndPosition(const Vector2& position);

private:
	// ��, ��ֹ� ���� �迭
	std::vector<DrawableActor*> map;

	// Start ����
	Start* start = nullptr;
	
	//End ����
	Player* player = nullptr;

};