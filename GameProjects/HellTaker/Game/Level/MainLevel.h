#pragma once

#include "Level/Level.h"
#include "Container/List.h"

struct MainItem
{
	using OnSelected = void (*)();

	MainItem(const char* text, OnSelected onSelected)
	{
		size_t length = strlen(text);
		mainText = new char[length + 1];
		strcpy_s(mainText, length + 1, text);

		this->onSelected = onSelected;
	}

	~MainItem()
	{
		delete[] mainText;
	}

	char* mainText;
	OnSelected onSelected;
};

class MainLevel : public Level
{
	RTTI_DECLARATIONS(MainLevel, Level)

public:
	MainLevel();
	~MainLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	int currentIndex = 0;
	Color selectedColor = Color::Red;
	Color unselectedColor = Color::White;

	List<MainItem*> mainItems;
	int length = 0;
};