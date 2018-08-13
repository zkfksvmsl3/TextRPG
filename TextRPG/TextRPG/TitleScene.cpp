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
		std::cout << "1. �����ϱ� : " << std::endl;
		std::cout << "2. �̾��ϱ� : " << std::endl;
		std::cout << "3. ������ : " << std::endl;
		std::cout << "======================================" << std::endl;

		std::cout << "(1 ~ 3) ������ �ּ��� :  ";
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
				std::cout << "�ε带 �����Ͽ����ϴ�.." << std::endl;
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
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� ! " << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			_getch();
			break;
		}
		
		system("cls");
	}

}
