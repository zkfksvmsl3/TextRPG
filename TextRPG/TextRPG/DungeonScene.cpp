#include "DungeonScene.h"

#include <iostream>
#include <conio.h>

#include "GameSystem.h"
#include "SceneManager.h"
#include "ParsingSystem.h"
#include "sParagraph.h"

DungeonScene::DungeonScene()
{
	iPlayerSelect = 0;
	_player = GameSystem::GetInstance()->GetCharacter();
}


DungeonScene::~DungeonScene()
{
	parser = new ParsingSystem();
	iBranch = 0;
	isQuit = false;
}

void DungeonScene::Init(int _index)
{
	system("cls");
	pargraphCount = 0;
	SetSceneType(eScene::SCENE_DUNGEON);

	paragraphList = parser->CSVParsing("DungeonScene.csv", &pargraphCount);

	std::cout << "<<������ �����Ͽ����ϴ�.>>" << std::endl;
	std::cout << "�÷��̾� ������ ����ؼ� ���� ��Ÿ���ϴ�." << std::endl;
	_getch();
}

void DungeonScene::Update()
{

	while (1)
	{
		std::cout << "���� ������ ���ðڽ��ϱ�? ( y / n )" ;
		std::cin >> chText;

		if ('y' == chText || 'Y' == chText)
		{
			DungeonStart();
			break;
		}
		else if ('n' == chText || 'N' == chText)
		{
			SceneManager::GetInstance()->ChangeScene(eScene::SCENE_VILLAGE, 0);
			break;
		}
		else if (std::cin.fail())
		{
			std::cout << "�߸��� ���� �Է� �߽��ϴ�. �ٽ� �Է��� �ּ��� !" << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}
		else
		{
			std::cout << "�߸��� ���� �Է� �߽��ϴ�. �ٽ� �Է��� �ּ��� !" << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}
	}
}

void DungeonScene::DungeonStart()
{
	GameSystem::GetInstance()->InitPosen(_player);
	
	iBranch = 0;
	while (false == isQuit)
	{
		if (iBranch == 11)
		{
			paragraphList[iBranch].Process(&iBranch, sceneType, &isQuit);
		}
		if (iBranch < pargraphCount)
		{
			paragraphList[iBranch].Process(&iBranch, sceneType, &isQuit);
		}

	}
}
