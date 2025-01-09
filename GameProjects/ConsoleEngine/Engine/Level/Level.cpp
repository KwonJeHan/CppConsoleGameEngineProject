#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"
#include <iostream>

Level::Level()
{
}

Level::~Level()
{
	// �޸� ����
	for (Actor* actor : actors)
	{
		delete actor;
	}
}

void Level::AddActor(Actor* newActor)
{
	actors.PushBack(newActor);
}

void Level::DestroyActor()
{
	// ���� ��ȸ �� ���� ��û�� ���͸� ó��
	for (int ix = 0; ix < actors.Size(); ++ix)
	{
		delete actors[ix];
		actors[ix] = nullptr;
		actors.Erase(ix);
	}
}

void Level::Update(float deltaTime)
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Update �Լ� ȣ��
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Update(deltaTime);
	}
}

void Level::Draw()
{
	// ������ ���Ե� ���͸� ��ȸ�ϸ鼭 Draw �Լ� ȣ��
	for (Actor* actor : actors)
	{
		// ���Ͱ� ��Ȱ��ȭ �����̰ų�, ���� ��û�� ��� �ǳʶٱ�
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Draw();
	}
}