#include "TitleScene.h"

#include <Windows.h>
#include <iostream>
#include <conio.h>

#include "SceneManager.h"
#include "ParsingSystem.h"
#include "GameSystem.h"

TitleScene::TitleScene()
{
	
}

TitleScene::~TitleScene()
{

}

void TitleScene::Init(int _index)
{
}

void TitleScene::Update()
{
	bool isStart = false;
	bool _isLoad = false;
	while (false == isStart)
	{
		std::cout << "======================================" << std::endl;
		std::cout << "1. 새로하기 : " << std::endl;
		std::cout << "2. 이어하기 : " << std::endl;
		std::cout << "3. 끝내기 : " << std::endl;
		std::cout << "======================================" << std::endl;

		std::cout << "(1 ~ 3) 선택해 주세요 :  ";
		std::cin >> iPlayerSelect;

		switch (iPlayerSelect)
		{
		case 1:
			SceneManager::GetInstance()->ChangeScene(eScene::SCENE_CREATECHACTER, 0);
			isStart = true;
			break;
		case 2:
			GameSystem::GetInstance()->Load(&_isLoad);

			if (true == _isLoad)
			{
				SceneManager::GetInstance()->ChangeScene(eScene::SCENE_VILLAGE, 0);
				isStart = true;

			}
			else
			{
				std::cout << "로드를 실패하였습니다.." << std::endl;
				system("pause");
				GameSystem::GetInstance()->StdCinClear();

				break;
			}

			break;
		case 3:
			isStart = true;
			GameSystem::GetInstance()->SetIsGameProgress(false);
			break;
		default:
			std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 ! " << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			_getch();
			break;
		}
		
		system("cls");
	}

}
