#include "BeginningVillageScene.h"

#include <conio.h>
#include <iostream>
#include <time.h>

#include "ParsingSystem.h"
#include "sParagraph.h"
#include "Item.h"
#include "GeneralStore.h"
#include "ArmsStore.h"
#include "DefensiveStore.h"
#include "GameSystem.h"
#include "Character.h"



BeginningVillageScene::BeginningVillageScene()
{
	iPlayerSelect = 0; 
	iRand = 0;
	iBranch = 0;
	isQuit = false;
	parser = new ParsingSystem();
	_character = GameSystem::GetInstance()->GetCharacter();
	
}

BeginningVillageScene::~BeginningVillageScene()
{
	delete parser;
}

void BeginningVillageScene::Init(int _index)
{
	system("cls");


}

void BeginningVillageScene::Update()
{
	srand((unsigned)time(NULL));
	
	while (1)
	{
		InitMap();

		std::cout << " ( 1 ~ 6 ) 선택해 주세요 : ";
		std::cin >> iPlayerSelect;

		switch (iPlayerSelect)
		{
		case 1:
			InitVillage(iRand);
			break;
		case 2:
			InitStore();
			break;
		case 3:
			// Save
			std::cout << "여관입니다." << std::endl;
			std::cout << "체력과 마나가 회복되었습니다!" << std::endl;
			_getch();
			_character->SetHp(_character->GetMaxHp());
			_character->SetMp(_character->GetMaxMp());

			GameSystem::GetInstance()->Save(_character);
			break;
		case 4:
			SceneManager::GetInstance()->ChangeScene(eScene::SCENE_DUNGEON, 0);
			break;
		case 5:
			_character->PlayerState();
			break;
		case 6:
			std::cout << " 게 임 종 료 " << std::endl;
			_getch();
			GameSystem::GetInstance()->SetIsGameProgress(false);
			break;
		default:
			std::cout << "잘못된 값을 입력 했습니다. 다시 입력해 주세요 !!" << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			system("cls");

			break;
		}

		if (1 <= iPlayerSelect || 6 >= iPlayerSelect)
		{
			break;
		}

	}

}

void BeginningVillageScene::InitMap()
{
	std::cout << "=======================================" << std::endl;
	std::cout << "1. 마을 " << std::endl;
	std::cout << "2. 상점 " << std::endl;
	std::cout << "3. 여관 " << std::endl;
	std::cout << "4. 던전 " << std::endl;
	std::cout << "5. 상태 " << std::endl;
	std::cout << "6. 종료 " << std::endl;
	std::cout << "=======================================" << std::endl;
}

void BeginningVillageScene::InitVillage(int iRandom)
{
	pargraphCount = 0;
	paragraphList = parser->CSVParsing("BeginningVillage.csv", &pargraphCount);
	SetSceneType(eScene::SCENE_VILLAGE);
	VillageUpdate(iRandom);
}

void BeginningVillageScene::VillageUpdate(int iRandom)
{
	system("cls");
	while (false == isQuit)
	{
		iRandom = rand() % 10;

		if (iBranch < pargraphCount)
		{
			paragraphList[iBranch].Process(&iBranch, sceneType, &isQuit);

			if (3 == iBranch)
			{
				if (7 == iRandom)
				{
					iBranch = 4;
					_character->SetGold(10000);
				}

			}

		}

	}

	isQuit = false;
	iBranch = 0;
	system("cls");
}

void BeginningVillageScene::InitStore()
{
	system("cls");

	Item* item = new Item();
	Store* store = 0;

	while (1)
	{
		std::cout << "1. 잡화상점 2. 무기 상점 3. 방어구 상점 " << std::endl;
		std::cout << "어느 상점으로 이동 하시겠습니까? " << std::endl;
		std::cin >> iPlayerSelect;

		if (1 == iPlayerSelect)
		{
			store = new GeneralStore();
			store->ItemInit();
			break;
		}
		else if (2 == iPlayerSelect)
		{
			store = new ArmsStore();
			store->ItemInit();
			break;
		}
		else if (3 == iPlayerSelect)
		{
			store = new DefensiveStore();
			store->ItemInit();
			break;
		}
		else
		{
			std::cout << "잘못된 값을 입력 했습니다. 다시 입력해 주세요 !" << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}
	}
	
	store->EnterStore(_character);
}
 