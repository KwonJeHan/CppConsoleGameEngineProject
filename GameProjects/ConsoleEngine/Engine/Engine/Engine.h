#pragma once

// �Է� ó���� ���� ����ü
struct KeyState
{
	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��
	bool isKeyDown = false;

	// ���� �����ӿ� Ű�� ���ȴ��� Ȯ��
	bool wasKeyDown = false;
};

// ���� Ŭ����
class Engine
{
public:
	Engine();
	virtual ~Engine();


	// ���� ���� �Լ�
	void Run();

	// �Է� ���� �Լ�
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetGeyUp(int key);

	// ���� ���� �Լ�
	void QuitGame();

protected:
	void ProcessInput();				// �Է� ó��
	void Update(float deltaTime);		// Tick();
	void Draw();						// Render();

	// Ű ���� ����
	void SavePreviouseKeyStates();

private:

	// ������ �� ������ ����
	bool quit;

	// Ű ���¸� �����ϴ� �迭
	KeyState keyState[255];
};