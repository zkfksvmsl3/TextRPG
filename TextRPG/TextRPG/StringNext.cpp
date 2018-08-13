#include "StringNext.h"

#include <conio.h>
#include <iostream>

#include "SceneManager.h"
#include "GameSystem.h"

StringNext::StringNext()
{
}


StringNext::~StringNext()
{
}

void StringNext::Process(int* nextBranch, eScene type, bool* isQuit)
{
	Print();
	std::cout << " y / n ? ";
	while (1)
	{
		std::cin >> chText;
		std::cout << std::endl;

		if ('y' == chText || 'Y' == chText)
		{
			switch (type)
			{
			case eScene::SCENE_CREATECHACTER:
				SceneManager::GetInstance()->ChangeScene(eScene::SCENE_VILLAGE, 0);
				*isQuit = true;
				break;
			case eScene::SCENE_VILLAGE:
				*isQuit = true;
				break;
			}
			break;
		}
		else if ('n' == chText || 'N' == chText)
		{
			switch (type)
			{
			case eScene::SCENE_CREATECHACTER:
				*nextBranch = 1;
				system("cls");
				break;
			case eScene::SCENE_VILLAGE:
				*nextBranch = 1;
				break;
			}
			break;
		}
		else
		{
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
			GameSystem::GetInstance()->StdCinClear();

		}
	}
	
	
}
