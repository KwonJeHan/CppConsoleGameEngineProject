#include "GameLevel.h"
#include "Engine/Engine.h"
#include "Game/Game.h"

#include "Actor/Wall.h"
#include "Actor/Ground.h"
#include "Actor/Stone.h"
#include "Actor/Skeleton.h"
#include "Actor/Target.h"
#include "Actor/Spike.h"
#include "Actor/Gate.h"
#include "Actor/Key.h"
#include "Actor/Demon.h"
#include "Actor/Player.h"

#include "Engine/Timer.h"


GameLevel::GameLevel()
{
	fileIndex = Game::Get().index;
	SelectStage();
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	// 타겟 지점에 플레이어가 도착했는지 확인
	isStageClear = CheckStageClear();

	// 모든 스테이지가 클리어 됐는지 확인
	isGameClear = CheckGameClear();

	// 플레이어가 이동 가능 횟수를 초과했는지 확인
	isGameOver = CheckGameOver();


	// 스테이지 클리어 시 다음 스테이지
	if (isStageClear)
	{
		// 타이머
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}
		timer.Reset();

		// 커서 이동
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 20, (Engine::Get().ScreenSize().y / 2) - 2);

		// 메시지 출력
		Log("Stage Clear!");

		// 쓰레드 정지
		Sleep(2000);

		system("cls");

		Game::Get().NextLevel();
	}

	// 게임이 클리어 됐으면 게임 종료 처리
	if (isGameClear)
	{
		// 대략 한 프레임 정도의 시간 대기
		/*static float elapsedTime = 0.0f;
		elapsedTime += deltaTime;
		if (elapsedTime < 0.1f)
		{
			return;
		}*/

		// 타이머
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}

		// 커서 이동
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 20, (Engine::Get().ScreenSize().y / 2) - 2);

		// 메시지 출력
		Log("Game Clear!");

		// 쓰레드 정지
		Sleep(2000);

		// 게임 종료 처리
		Engine::Get().QuitGame();
	}

	// 게임 오버 됐으면 게임 재시작
	if (isGameOver)
	{
		// 타이머
		static Timer timer(0.1f);
		timer.Update(deltaTime);
		if (!timer.IsTimeOut())
		{
			return;
		}
		timer.Reset();

		// 커서 이동
		Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x + 20, (Engine::Get().ScreenSize().y / 2) - 2);

		// 메시지 출력
		Log("Game Over!");

		// 쓰레드 정지
		Sleep(2000);

		system("cls");

		// 스테이지 다시 시작
		Game::Get().ReLevel();

		//// 게임 종료 처리
		//Engine::Get().QuitGame();
	}
}

void GameLevel::Draw()
{
	Engine::Get().SetCursorPosition(Engine::Get().ScreenSize().x, Engine::Get().ScreenSize().y - 1);

	// 메시지 출력
	Log("남은 이동 횟수 : %d회, 가지고 있는 열쇠 개수 : %d개", (moveLimit - player->moveCount), player->hasKey);

	// 맵 그리기
	for (auto* actor : map)
	{
		// 플레이어 위치 확인
		if (actor->Position() == player->Position())
		{
			continue;
		}

		// 악마 위치 확인
		if (actor->Position() == demon->Position())
		{
			continue;
		}
		
		// 바위 위치 확인
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (actor->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 해골 위치 확인
		for (auto* skeleton : skeletons)
		{
			if (actor->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 열쇠 위치 확인
		for (auto* key : keys)
		{
			if (actor->Position() == key->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 문 위치 확인
		for (auto* gate : gates)
		{
			if (actor->Position() == gate->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		if (shouldDraw)
		{
			actor->Draw();
		}
	}

	// 타겟 그리기
	for (auto* target : targets)
	{
		// 플레이어 위치 확인
		if (target->Position() == player->Position())
		{
			continue;
		}

		// 바위 위치 확인
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (target->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 해골 위치 확인
		for (auto* skeleton : skeletons)
		{
			if (target->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 타겟 액터 그리기.
		if (shouldDraw)
		{
			target->Draw();
		}
	}

	// 가시 함정 그리기
	for (auto* spike : spikes)
	{
		// 플레이어 위치 확인
		if (spike->Position() == player->Position())
		{
			continue;
		}

		// 바위 위치 확인
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (spike->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 해골 위치 확인
		for (auto* skeleton : skeletons)
		{
			if (spike->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 가시 함정 액터 그리기.
		if (shouldDraw)
		{
			spike->Draw();
		}
	}

	// 열쇠 그리기
	for (auto* key : keys)
	{
		// 플레이어 위치 확인
		if (key->Position() == player->Position())
		{
			continue;
		}

		// 바위 위치 확인
		bool shouldDraw = true;
		for (auto* stone : stones)
		{
			if (key->Position() == stone->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 해골 위치 확인
		for (auto* skeleton : skeletons)
		{
			if (key->Position() == skeleton->Position())
			{
				shouldDraw = false;
				break;
			}
		}

		// 열쇠 액터 그리기.
		if (shouldDraw)
		{
			if (!key->isExpired)
			{
				key->Draw();
			}
		}
	}

	// 문 그리기	
	for (auto* gate : gates)
	{
		if (!gate->isExpired)
		{
			gate->Draw();
		}
	}

	// 바위 그리기.
	for (auto* stone : stones)
	{
		if (!stone->isExpired)
		{
			stone->Draw();
		}
	}

	// 해골 그리기
	for (auto* skeleton : skeletons)
	{
		if (!skeleton->isExpired)
		{
			skeleton->Draw();
		}
	}

	// 악마 그리기
	demon->Draw();

	// 플레이어 그리기.
	player->Draw();
}

bool GameLevel::CanPlayerMove(const Vector2& position)
{
	// 게임이 클리어된 경우 바로 종료
	if (isGameClear)
	{
		return false;
	}

	// 바위 검색
	Stone* searchedStone = nullptr;
	for (auto* stone : stones)
	{
		if (stone->Position() == position)
		{
			searchedStone = stone;
			break;
		}
	}

	// 해골 검색
	Skeleton* searchedSkeleton = nullptr;
	for (auto* skeleton : skeletons)
	{
		if (skeleton->Position() == position)
		{
			searchedSkeleton = skeleton;
			break;
		}
	}

	// 문 검색
	Gate* searchedgate = nullptr;
	for (auto* gate : gates)
	{
		if (gate->Position() == position)
		{
			searchedgate = gate;
			break;
		}
	}

	// 열쇠 검색
	Key* searchedkey = nullptr;
	for (auto* key : keys)
	{
		if (key->Position() == position)
		{
			searchedkey = key;
			break;
		}
	}

	// 바위가 있을 때 처리
	if (searchedStone)
	{
		// 이동 방향
		int directionX = position.x - player->Position().x;
		int directionY = position.y - player->Position().y;

		// 바위가 이동할 새 위치
		Vector2 newPosition = searchedStone->Position() + Vector2(directionX, directionY);

		// 추가 검색 (바위)
		for (auto* stone : stones)
		{
			// 예외 처리
			if (stone == searchedStone)
			{
				continue;
			}

			// 이동할 위치에 다른 바위가 있다면 이동 불가
			if (stone->Position() == newPosition)
			{
				return false;
			}
		}

		// 추가 검색 (해골)
		for (auto* skeleton : skeletons)
		{
			// 예외 처리
			if (skeleton == searchedSkeleton)
			{
				continue;
			}

			// 이동할 위치에 해골이 있다면 이동 불가
			if (skeleton->Position() == newPosition)
			{
				return false;
			}
		}

		// 추가 검색 (문)
		for (auto* gate : gates)
		{
			// 예외 처리
			if (gate == searchedgate)
			{
				continue;
			}

			// 이동할 위치에 문이 있다면 이동 불가
			if (gate->Position() == newPosition)
			{
				return false;
			}
		}

		// 추가 검색 (열쇠)
		for (auto* key : keys)
		{
			// 예외 처리
			if (key == searchedkey)
			{
				continue;
			}

			// 이동할 위치에 열쇠가 있다면 이동 가능
			if (key->Position() == newPosition)
			{
				return true;
			}
		}

		// 추가 검색(맵)
		for (auto* actor : map)
		{
			// 이동하려는 위치에 있는 액터 검색
			if (actor->Position() == newPosition)
			{
				// 형변환을 통해 물체의 타입 확인

				// 이동하려는 위치에 벽이 있으면 이동 불가
				if (actor->As<Wall>())
				{
					return false;
				}

				// 이동하려는 위치에 악마가 있으면 이동 불가
				if (actor->Position() == demon->Position())
				{
					return false;
				}

				// 땅이나 타겟, 가시 함정이면 이동 가능
				if (actor->As<Ground>() || actor->As<Target>() || actor->As<Spike>())
				{
					// 바위 이동 처리
					searchedStone->SetPosition(newPosition);

					// 게임 클리어 여부 확인
					//isGameClear = CheckGameClear();

					// 바위나 해골은 이동, 캐릭터는 제자리
					return false;
				}
			}
		}
	}

	// 해골이 있을 때 처리
	if (searchedSkeleton)
	{
		// 이동 방향
		int directionX = position.x - player->Position().x;
		int directionY = position.y - player->Position().y;

		// 해골이 이동할 새 위치
		Vector2 newPosition = searchedSkeleton->Position() + Vector2(directionX, directionY);

		// 추가 검색 (해골)
		for (auto* skeleton : skeletons)
		{
			// 예외 처리
			if (skeleton == searchedSkeleton)
			{
				continue;
			}

			// 이동할 위치에 다른 해골이 있다면 파괴
			if (skeleton->Position() == newPosition)
			{
				Engine::Get().DestroyActor(searchedSkeleton);
				return false;
			}
		}

		// 추가 검색 (바위)
		for (auto* stone : stones)
		{
			// 예외 처리
			if (stone == searchedStone)
			{
				continue;
			}

			// 이동할 위치에 바위가 있다면 파괴
			if (stone->Position() == newPosition)
			{
				Engine::Get().DestroyActor(searchedSkeleton);
				return false;
			}
		}

		// 추가 검색 (문)
		for (auto* gate : gates)
		{
			// 예외 처리
			if (gate == searchedgate)
			{
				continue;
			}

			// 이동할 위치에 문이 있다면 파괴
			if (gate->Position() == newPosition)
			{
				Engine::Get().DestroyActor(searchedSkeleton);
				return false;
			}
		}

		// 추가 검색 (열쇠)
		for (auto* key : keys)
		{
			// 예외 처리
			if (key == searchedkey)
			{
				continue;
			}

			// 이동할 위치에 열쇠가 있다면 이동 가능
			if (key->Position() == newPosition)
			{
				return true;
			}
		}

		// 추가 검색(맵)
		for (auto* actor : map)
		{
			// 이동하려는 위치에 있는 액터 검색
			if (actor->Position() == newPosition)
			{
				// 형변환을 통해 물체의 타입 확인

				// 이동하려는 위치에 벽이 있으면 파괴
				if (actor->As<Wall>())
				{
					Engine::Get().DestroyActor(searchedSkeleton);
					return false;
				}

				// 이동하려는 위치에 악마가 있으면 파괴
				if (actor->Position() == demon->Position())
				{
					Engine::Get().DestroyActor(searchedSkeleton);
					return false;
				}

				// 땅이나 타겟, 가시 함정이면 이동 가능
				if (actor->As<Ground>() || actor->As<Target>() || actor->As<Spike>() || actor->As<Key>())
				{
					// 해골 이동 처리
					searchedSkeleton->SetPosition(newPosition);

					// 게임 클리어 여부 확인
					//isGameClear = CheckGameClear();

					// 바위나 해골은 이동, 캐릭터는 제자리
					return false;
				}
			}
		}
	}

	// 문이 있을 때 처리
	if (searchedgate)
	{
		if (player->hasKey > 0)
		{
			--(player->hasKey);
			Engine::Get().DestroyActor(searchedgate);
			return true;
		}
		else
		{
			return false;
		}
	}

	// 열쇠가 있을 때 처리
	if (searchedkey)
	{
		++(player->hasKey);
		Engine::Get().DestroyActor(searchedkey);
		return true;
	}


	// 이동하려는 위치에 벽이 있는지 확인
	DrawableActor* searchedActor = nullptr;

	// 먼저 이동하려는 액터 찾기
	for (auto* actor : map)
	{
		if (actor->Position() == position)
		{
			searchedActor = actor;
			break;
		}
	}

	// 검색한 액터가 벽인지 확인
	if (searchedActor->As<Wall>())
	{
		return false;
	}

	// 검색한 액터가 악마인지 확인
	if (searchedActor != nullptr)
	{
		if (searchedActor->Position() == demon->Position())
		{
			return false;
		}
	}

	// 검색한 액터가 이동 가능한 액터(땅/타겟)인지 확인
	if (searchedActor->As<Ground>() || searchedActor->As<Target>())
	{
		return true;
	}

	// 검색한 액터가 가시 함정인지 확인
	if (searchedActor->As<Spike>())
	{
		++(player->moveCount);
		return true;
	}

	return false;
}

void GameLevel::SelectStage()
{
	switch (fileIndex)
	{
	case 0:
		TextFileRead("../Assets/Maps/stage1.txt");
		moveLimit = 22;
		break;
	case 1:
		TextFileRead("../Assets/Maps/stage2.txt");
		moveLimit = 25;
		break;
	case 2:
		TextFileRead("../Assets/Maps/stage3.txt");
		moveLimit = 40;
		break;
	case 3:
		TextFileRead("../Assets/Maps/stage4.txt");
		moveLimit = 15;
		lastStage = true;
		break;
	}
}

void GameLevel::TextFileRead(const char* filename)
{
	// 커서 감추기.
	Engine::Get().SetCursorType(CursorType::NoCursor);

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
			actors.PushBack(wall);
			map.PushBack(wall);
		}

		// 맵 문자가 0이면 그라운드 액터 생성
		else if (mapChar == '0')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);
		}

		// 맵 문자가 b이면 바위 액터 생성
		else if (mapChar == 'b')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Stone* stone = new Stone(Vector2(xPosition, yPosition));
			actors.PushBack(stone);
			stones.PushBack(stone);
		}

		// 맵 문자가 s이면 해골 액터 생성
		else if (mapChar == 's')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Skeleton* skeleton = new Skeleton(Vector2(xPosition, yPosition));
			actors.PushBack(skeleton);
			skeletons.PushBack(skeleton);
		}

		// 맵 문자가 2이면 열쇠 액터 생성
		else if (mapChar == '2')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Key* key = new Key(Vector2(xPosition, yPosition));
			actors.PushBack(key);
			keys.PushBack(key);
		}

		// 맵 문자가 3이면 문 액터 생성
		else if (mapChar == '3')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			Gate* gate = new Gate(Vector2(xPosition, yPosition));
			actors.PushBack(gate);
			gates.PushBack(gate);
		}

		// 맵 문자가 t이면 타겟 액터 생성
		else if (mapChar == 't')
		{
			Target* target = new Target(Vector2(xPosition, yPosition));
			actors.PushBack(target);
			map.PushBack(target);
			targets.PushBack(target);
		}

		// 맵 문자가 k이면 가시 함정 액터 생성
		else if (mapChar == 'k')
		{
			Spike* spike = new Spike(Vector2(xPosition, yPosition));
			actors.PushBack(spike);
			map.PushBack(spike);
			spikes.PushBack(spike);
		}

		// 맵 문자가 d이면 악마 액터 생성
		else if (mapChar == 'd')
		{
			Ground* ground = new Ground(Vector2(xPosition, yPosition));
			actors.PushBack(ground);
			map.PushBack(ground);

			demon = new Demon(Vector2(xPosition, yPosition));
			actors.PushBack(demon);
		}

		// 맵 문자가 p이면 플레이어 액터 생성
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

	// 버퍼 삭제
	delete[] buffer;

	// 파일 닫기
	fclose(file);
}

bool GameLevel::CheckStageClear()
{
	bool stageClear = 0;
	for (auto* target : targets)
	{
		if ((player->Position() == target->Position()) && !lastStage)
		{
			++stageClear;
			continue;
		}
	}
	return stageClear;
}

bool GameLevel::CheckGameClear()
{
	bool gameClear = 0;
	for (auto* target : targets)
	{
		if ((player->Position() == target->Position()) && lastStage)
		{
			++gameClear;
			continue;
		}
	}
	return gameClear;
}

bool GameLevel::CheckGameOver()
{
	return player->moveCount >= moveLimit;
}
