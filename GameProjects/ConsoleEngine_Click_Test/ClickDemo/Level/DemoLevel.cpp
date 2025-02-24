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
	// 맵 파일 불러와 레벨 로드.
	// 파일 읽기
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

	// 파일 처리
	if (file == nullptr)
	{
		std::cout << "맵 파일 열기 실패\n";
		__debugbreak();
		return;
	}

	// 파일 읽기
	// 끝 위치로 이동
	fseek(file, 0, SEEK_END);

	// 이동한 위치의 FP 가져오기
	size_t readSize = ftell(file);

	// FP 원위치
	//fseek(file, 0, SEEK_SET);
	rewind(file);

	// 파일 읽어서 버퍼에 담기
	char* buffer = new char[readSize + 1];
	size_t bytesRead = fread(buffer, 1, readSize, file);

	if (readSize != bytesRead)
	{
		std::cout << "읽어온 크기가 다름\n";
		__debugbreak();
		return;
	}

	buffer[readSize] = '\0';

	// 파일 읽을 때 사용할 인덱스
	int index = 0;
	// 좌표 계산을 위한 변수 선언
	int xPosition = (int)(Engine::Get().ScreenSize().x + 17);
	int yPosition = (int)(Engine::Get().ScreenSize().y / 2);


	// 해석 (파싱-Parcing)
	while (index < (int)bytesRead)
	{
		// 한 문자씩 읽기
		char mapChar = buffer[index++];

		// 개행 문자인 경우 처리
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

		// 맵 문자가 1이면 Wall 액터 생성
		if (mapChar == '1')
		{
			//std::cout << 'A';
			//AddActor(new Wall(Vector2(xPosition, yPosition)));
			Wall* wall = new Wall(Vector2(xPosition, yPosition));
			actors.emplace_back(wall);
			map.emplace_back(wall);
		}

		// 맵 문자가 0이면 그라운드 액터 생성
		else if (mapChar == '0')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.emplace_back(ground);
			map.emplace_back(ground);
		}

		// 맵 문자가 p이면 플레이어 액터 생성
		else if (mapChar == '3')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.emplace_back(ground);
			map.emplace_back(ground);

			start = new Start(Vector2(xPosition, yPosition));
			actors.emplace_back(player);
		}

		// 맵 문자가 p이면 플레이어 액터 생성
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

	// 버퍼 삭제
	delete[] buffer;

	// 파일 닫기
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

