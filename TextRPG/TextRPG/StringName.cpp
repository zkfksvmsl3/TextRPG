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
	std::cout << "캐릭터 이름은 ?";
	std::cin >> sName;
	std::cout << "캐릭터의 이름은 " << sName << " 입니다." << std::endl;

	GameSystem::GetInstance()->SetPlayerName(sName);
	_getch();
}
