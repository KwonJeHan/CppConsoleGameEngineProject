#include "GameLevel.h"
#include "Engine/Engine.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Stone.h"
#include "Actor/Skeleton.h"
#include "Actor/Target.h"
#include "Actor/Spike.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"

GameLevel::GameLevel()
{
    // Ŀ�� ���߱�.
    Engine::Get().SetCursorType(CursorType::NoCursor);

    // �� ���� �ҷ��� ���� �ε�.
	// ���� �б�
	FILE* file = nullptr;
	fopen_s(&file, "../Assets/Maps/Map.txt", "rb");

	// ���� ó��
	if (file == nullptr)
	{
		std::cout << "�� ���� ���� ����\n";
		__debugbreak();
		return;
	}

	// ���� �б�
	// �� ��ġ�� �̵�
	fseek(file, 0, SEEK_END);

	// �̵��� ��ġ�� FP ��������
	size_t readSize = ftell(file);

	// FP ����ġ
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// ���� �о ���ۿ� ���
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "�о�� ũ�Ⱑ �ٸ�\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// ���� ���� �� ����� �ε���
	int index = 0;

	// ��ǥ ����� ���� ���� ����
	int xPosition = 0;
	int yPosition = 0;

	// �ؼ� (�Ľ�-Parcing)
	while (index < (int)bytesRead)
	{
		// �� ���ھ� �б�
		char mapChar = buffer[index++];
		
		// ���� ������ ��� ó��
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = 0;
			continue;
		}

		// �� ���ڰ� 1�̸� Wall ���� ����
		if (mapChar == '1')
		{
			//std::cout << 'A';
			//AddActor(new Wall(Vector2(xPosition, yPosition)));
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// �� ���ڰ� 0�̸� �׶��� ���� ����
		else if (mapChar == '0')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		// �� ���ڰ� b�̸� ���� ���� ����
		else if (mapChar == 'b')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Stone* stone = new Stone(Vector2(xPosition, yPosition));
			actors.PushBack(stone);
			stones.PushBack(stone);
		}

		// �� ���ڰ� s�̸� �ذ� ���� ����
		else if (mapChar == 's')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Skeleton* skeleton = new Skeleton(Vector2(xPosition, yPosition));
			actors.PushBack(skeleton);
			skeletons.PushBack(skeleton);
		}

		// �� ���ڰ� t�̸� Ÿ�� ���� ����
		else if (mapChar == 't')
		{
			Target* target = new Target(Vector2(xPosition, yPosition));
			actors.PushBack(target);
			map.PushBack(target);
			targets.PushBack(target);
		}

		// �� ���ڰ� k�̸� ���� ���� ���� ����
		else if (mapChar == 'k')
		{
			Spike* spike = new Spike(Vector2(xPosition, yPosition));
			actors.PushBack(spike);
			map.PushBack(spike);
			spikes.PushBack(spike);
		}

		// �� ���ڰ� p�̸� �÷��̾� ���� ����
		else if (mapChar == 'p')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
			
			player = new Player(Vector2(xPosition, yPosition), this);
			actors.PushBack(player);
		}

		++xPosition;
		
	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// Ÿ�� ������ �÷��̾ �����ߴ��� Ȯ��
	isGameClear = CheckGameClear();

	// �÷��̾ �̵� ���� Ƚ���� �ʰ��ߴ��� Ȯ��
	isGameOver = CheckGameOver();

	// ������ Ŭ���� ������ ���� ���� ó��
	if (isGameClear)
	{
		// �뷫 �� ������ ������ �ð� ���
		/*static float elapsedTime = 0.0f;
		elapsedTime += deltaTime;
		if (elapsedTime < 0.1f)
		{
			return;
		}*/

		// Ÿ�̸�
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		// Ŀ�� �̵�
		Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		// �޽��� ���
		Log("Game Clear!");

		// ������ ����
		Sleep(2000);

		// ���� ���� ó��
		Engine::Get().QuitGame();
	}

	// ���� ���� ������ ���� ���� ó��
	if (isGameOver)
	{
		// Ÿ�̸�
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		// Ŀ�� �̵�
		Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y);

		// �޽��� ���
		Log("Game Over!");

		// ������ ����
		Sleep(2000);

		// ���� ���� ó��
		Engine::Get().QuitGame();
	}
}

void GameLevel::Draw()
{
	Engine::Get().SetCursorPosition(0, Engine::Get().ScreenSize().y - 1);

	// �޽��� ���
	Log("���� �̵� Ƚ�� : %dȸ", moveLimit - player->moveCount);

	// �� �׸���
	for (auto* actor : map)
	{
		// �÷��̾� ��ġ Ȯ��
		if (actor->Position() == player->Position())
		{
			continue;
		}
		
		// ���� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (actor->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		for (auto* skeleton : skeletons)
		{
			if (actor->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// ���� ��ġ Ȯ��


		// �� ��ġ Ȯ��


		if (shouldDraw)
		{
			actor->Draw();
		}
	}

	// Ÿ�� �׸���
	for (auto* target : targets)
	{
		// �÷��̾� ��ġ Ȯ��
		if (target->Position() == player->Position())
		{
			continue;
		}

		// ���� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (target->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		for (auto* skeleton : skeletons)
		{
			if (target->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// Ÿ�� ���� �׸���.
		if (shouldDraw)
		{
			target->Draw();
		}
	}

	// ���� ���� �׸���
	for (auto* spike : spikes)
	{
		// �÷��̾� ��ġ Ȯ��
		if (spike->Position() == player->Position())
		{
			continue;
		}

		// ���� ��ġ Ȯ��
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (spike->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		for (auto* skeleton : skeletons)
		{
			if (spike->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// ���� ���� ���� �׸���.
		if (shouldDraw)
		{
			if ((player->moveCount) % 2)
			{
				spike->active = true;
				spike->Draw();
			}
			else
			{
				spike->active = false;
				spike->Draw();
			}
		}
	}

	// ���� �׸���

	// �� �׸���

	// �Ǹ� �׸���

	// ���� �׸���.
	for (auto* stone : stones)
	{
		stone->Draw();
	}

	// �ذ� �׸���
	for (auto* skeleton : skeletons)
	{
		if (!skeleton->isExpired)
		{
			skeleton->Draw();
		}
	}

	// �÷��̾� �׸���.
	player->Draw();
}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	// ������ Ŭ����� ��� �ٷ� ����
	if (isGameClear)
	{
		return false;
	}

	// ���� �˻�
	Stone* searchedStone = nullptr;
	for (auto* stone : stones)
	{
		if (stone->Position() == position)
		{
			searchedStone = stone;
			break;
		}
	}

	// �ذ� �˻�
	Skeleton* searchedSkeleton = nullptr;
	for (auto* skeleton : skeletons)
	{
		if (skeleton->Position() == position)
		{
			searchedSkeleton = skeleton;
			break;
		}
	}

	// ������ ���� �� ó��
	if (searchedStone)
	{
		// �̵� ����
		int directionX = position.x - player->Position().x;
		int directionY = position.y - player->Position().y;

		// ������ �̵��� �� ��ġ
		Vector2 newPosition = searchedStone->Position() + Vector2(directionX, directionY);

		// �߰� �˻� (����)
		for (auto* stone : stones)
		{
			// ���� ó��
			if (stone == searchedStone)
			{
				continue;
			}

			// �̵��� ��ġ�� �ٸ� ������ �ִٸ� �̵� �Ұ�
			if (stone->Position() == newPosition)
			{
				return false;
			}
		}

		// �߰� �˻� (�ذ�)
		for (auto* skeleton : skeletons)
		{
			// ���� ó��
			if (skeleton == searchedSkeleton)
			{
				continue;
			}

			// �̵��� ��ġ�� �ٸ� �ذ��� �ִٸ� �̵� �Ұ�
			if (skeleton->Position() == newPosition)
			{
				return false;
			}
		}

		// �߰� �˻�(��)
		for (auto* actor : map)
		{
			// �̵��Ϸ��� ��ġ�� �ִ� ���� �˻�
			if (actor->Position() == newPosition)
			{
				// ����ȯ�� ���� ��ü�� Ÿ�� Ȯ��

				// �̵��Ϸ��� ��ġ�� ���� ������ �̵� �Ұ�
				if (actor->As<Wall>())
				{
					return false;
				}

				// ���̳� Ÿ��, ���� �����̸� �̵� ����
				if (actor->As<Ground>() || actor->As<Target>() || actor->As<Spike>())
				{
					// �ڽ� �̵� ó��
					searchedStone->SetPosition(newPosition);

					// ���� Ŭ���� ���� Ȯ��
					//isGameClear = CheckGameClear();

					// �ڽ��� �ذ��� �̵�, ĳ���ʹ� ���ڸ�
					return false;
				}
			}
		}
	}

	// �ذ��� ���� �� ó��
	if (searchedSkeleton)
	{
		// �̵� ����
		int directionX = position.x - player->Position().x;
		int directionY = position.y - player->Position().y;

		// ������ �̵��� �� ��ġ
		Vector2 newPosition = searchedSkeleton->Position() + Vector2(directionX, directionY);

		// �߰� �˻� (�ذ�)
		for (auto* skeleton : skeletons)
		{
			// ���� ó��
			if (skeleton == searchedSkeleton)
			{
				continue;
			}

			// �̵��� ��ġ�� �ٸ� �ذ��� �ִٸ� �ı�
			if (skeleton->Position() == newPosition)
			{
				Engine::Get().DestroyActor(searchedSkeleton);
				return false;
			}
		}

		// �߰� �˻� (����)
		for (auto* stone : stones)
		{
			// ���� ó��
			if (stone == searchedStone)
			{
				continue;
			}

			// �̵��� ��ġ�� �ٸ� ������ �ִٸ� �ı�
			if (stone->Position() == newPosition)
			{
				Engine::Get().DestroyActor(searchedSkeleton);
				return false;
			}
		}

		// �߰� �˻�(��)
		for (auto* actor : map)
		{
			// �̵��Ϸ��� ��ġ�� �ִ� ���� �˻�
			if (actor->Position() == newPosition)
			{
				// ����ȯ�� ���� ��ü�� Ÿ�� Ȯ��

				// �̵��Ϸ��� ��ġ�� ���� ������ �ı�
				if (actor->As<Wall>())
				{
					Engine::Get().DestroyActor(searchedSkeleton);
					return false;
				}

				// ���̳� Ÿ��, ���� �����̸� �̵� ����
				if (actor->As<Ground>() || actor->As<Target>() || actor->As<Spike>())
				{
					// �ذ� �̵� ó��
					searchedSkeleton->SetPosition(newPosition);

					// ���� Ŭ���� ���� Ȯ��
					//isGameClear = CheckGameClear();

					// �ڽ��� �ذ��� �̵�, ĳ���ʹ� ���ڸ�
					return false;
				}
			}
		}
	}

	// �̵��Ϸ��� ��ġ�� ���� �ִ��� Ȯ��
	DrawableActor* searchedActor = nullptr;

	// ���� �̵��Ϸ��� ���� ã��
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// �˻��� ���Ͱ� ������ Ȯ��
	if (searchedActor->As<Wall>())
	{
		return false;
	}

	// �˻��� ���Ͱ� �̵� ������ ����(��/Ÿ��)���� Ȯ��
	if (searchedActor->As<Ground>() || searchedActor->As<Target>())
	{
		return true;
	}

	// �˻��� ���Ͱ� ���� �������� Ȯ��
	if (searchedActor->As<Spike>())
	{
		if ((player->moveCount) % 2)
		{
			++(player->moveCount);
		}
		return true;
	}

	return false;
}

//bool GameLevel::CheckGameClear()
//{
//	// ���� Ȯ���� ���� ����
//	int currentScore = 0;
//	int targetScore = targets.Size();
//
//	// Ÿ�� ��ġ�� ��ġ�� �ڽ� ���� ����
//	for (auto* stone : stones)
//	{
//		for (auto* target : targets)
//		{
//			// ���� Ȯ��
//			if (stone->Position() == target->Position())
//			{
//				++currentScore;
//				continue;
//			}
//		}
//	}
//
//	// ŉ���� ������ ��ǥ ������ ������ ��
//	return currentScore == targetScore;
//}

bool GameLevel::CheckGameClear()
{
	bool gameclear = 0;
	for (auto* target : targets)
	{
		if (player->Position() == target->Position())
		{
			++gameclear;
			continue;
		}
	}
	return gameclear;
}

bool GameLevel::CheckGameOver()
{
	return player->moveCount == moveLimit;
}
