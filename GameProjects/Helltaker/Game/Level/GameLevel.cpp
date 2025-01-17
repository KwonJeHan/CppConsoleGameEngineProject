#include "GameLevel.h"
#include "Engine/Engine.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Stone.h"
#include "Actor/Skeleton.h"
#include "Actor/Target.h"
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

		// �� ���ڰ� .�̸� �׶��� ���� ����
		else if (mapChar == '.')
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
}

void GameLevel::Draw()
{
	// �� �׸���.
	for (auto* actor : map)
	{
		// �÷��̾� ��ġ Ȯ��
		if (actor->Position() == player->Position())
		{
			continue;
		}

		// ���� ��ġ Ȯ��
		bool shouldDrawB = true;
		for (auto* stone : stones)
		{
			if (actor->Position() == stone->Position())
			{
				shouldDrawB = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		bool shouldDrawS = true;
		for (auto* skeleton : skeletons)
		{
			if (actor->Position() == skeleton->Position())
			{
				shouldDrawS = false;
				break;
			}
		}

		if (shouldDrawB && shouldDrawS)
		{
			actor->Draw();
		}
	}

	// Ÿ�� �׸���.
	for (auto* target : targets)
	{
		// �÷��̾� ��ġ Ȯ��
		if (target->Position() == player->Position())
		{
			continue;
		}

		// ���� ��ġ Ȯ��
		bool shouldDrawB = true;
		for (auto* stone : stones)
		{
			if (target->Position() == stone->Position())
			{
				shouldDrawB = false;
				break;
			}
		}

		// �ذ� ��ġ Ȯ��
		bool shouldDrawS = true;
		for (auto* skeleton : skeletons)
		{
			if (target->Position() == skeleton->Position())
			{
				shouldDrawS = false;
				break;
			}
		}

		// �� ���� �׸���.
		if (shouldDrawB && shouldDrawS)
		{
			target->Draw();
		}
	}

	// ���� �׸���.
	for (auto* stone : stones)
	{
		stone->Draw();
	}

	// �ذ� �׸���
	for (auto* skeleton : skeletons)
	{
		skeleton->Draw();
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

				// ���̳� Ÿ���̸� �̵� ����
				if (actor->As<Ground>() || actor->As<Target>())
				{
					// �ڽ� �̵� ó��
					searchedStone->SetPosition(newPosition);

					// ���� Ŭ���� ���� Ȯ��
					isGameClear = CheckGameClear();

					return true;
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

	return false;
}

bool GameLevel::CheckGameClear()
{
	// ���� Ȯ���� ���� ����
	int currentScore = 0;
	int targetScore = targets.Size();

	// Ÿ�� ��ġ�� ��ġ�� �ڽ� ���� ����
	for (auto* stone : stones)
	{
		for (auto* target : targets)
		{
			// ���� Ȯ��
			if (stone->Position() == target->Position())
			{
				++currentScore;
				continue;
			}
		}
	}

	// ŉ���� ������ ��ǥ ������ ������ ��
	return currentScore == targetScore;
}