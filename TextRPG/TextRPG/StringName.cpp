#include "StringName.h"

#include <iostream>
#include <conio.h>

#include "GameSystem.h"
StringName::StringName()
{
}


StringName::~StringName()
{
}

void StringName::Process(int * nextBranch, eScene type, bool * isQuit)
{
	Print();
	*nextBranch = 1;
	std::cout << "ĳ���� �̸��� ?";
	std::cin >> sName;
	std::cout << "ĳ������ �̸��� " << sName << " �Դϴ�." << std::endl;

	GameSystem::GetInstance()->SetPlayerName(sName);
	_getch();
}
