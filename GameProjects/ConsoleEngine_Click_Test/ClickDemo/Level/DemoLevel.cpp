#include "DemoLevel.h"
#include "Engine/Engine.h"

#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Algorithm/Node.h"
#include "Algorithm/AStar.h"

DemoLevel::DemoLevel()
{

	/*AddActor(new Start());

	
	AddActor(new Player());*/
}

void DemoLevel::Update(float deltaTime)
{
}

void DemoLevel::Draw()
{
}

void DemoLevel::TextFileRead(const char* filename)
{
	// �� ���� �ҷ��� ���� �ε�.
	// ���� �б�
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

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
	int xPosition = (int)(Engine::Get().ScreenSize().x + 17);
	int yPosition = (int)(Engine::Get().ScreenSize().y / 2);


	// �ؼ� (�Ľ�-Parcing)
	while (index < (int)bytesRead)
	{
		// �� ���ھ� �б�
		char mapChar = buffer[index++];

		// ���� ������ ��� ó��
		if (mapChar == '\n')
		{
			++yPosition;
			xPosition = (Engine::Get().ScreenSize().x + 17);
			continue;
		}

		if (mapChar == ' ')
		{
			++xPosition;
			continue;
		}

		// �� ���ڰ� 1�̸� Wall ���� ����
		if (mapChar == '1')
		{
			//std::cout << 'A';
			//AddActor(new Wall(Vector2(xPosition, yPosition)));
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.emplace_back(wall);
			map.emplace_back(wall);
		}

		// �� ���ڰ� 0�̸� �׶��� ���� ����
		else if (mapChar == '0')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.emplace_back(ground);
			map.emplace_back(ground);
		}

		// �� ���ڰ� p�̸� �÷��̾� ���� ����
		else if (mapChar == '3')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.emplace_back(ground);
			map.emplace_back(ground);

			start = new Start(Vector2(xPosition, yPosition));
			actors.emplace_back(player);
		}

		// �� ���ڰ� p�̸� �÷��̾� ���� ����
		else if (mapChar == '2')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.emplace_back(ground);
			map.emplace_back(ground);

			player = new Player(Vector2(xPosition, yPosition));
			actors.emplace_back(player);
		}

		++xPosition;

	}

	// ���� ����
	delete[] buffer;

	// ���� �ݱ�
	fclose(file);
}

bool DemoLevel::CanStartPosition(const Vector2& position)
{
	return false;
}

bool DemoLevel::CanEndPosition(const Vector2& position)
{
	return false;
}

