#include "StringBranch.h"

#include <conio.h>
#include <iostream>

#include "GameSystem.h"
#include "Character.h"
StringBranch::StringBranch()
{
}


StringBranch::~StringBranch()
{
}

void StringBranch::Process(int* nextBranch, eScene type, bool * isQuit)
{
	Print();

	while (true)
	{
		std::cout << "������ ��ȣ�� ? : ";

		std::cin >> iPlayerSelect;

		if (type == eScene::SCENE_CREATECHACTER)
		{
			if (2 == iPlayerSelect)
			{
				*nextBranch = iPlayerSelect;
				GameSystem::GetInstance()->PlayerInit(iPlayerSelect);
				break;
			}
			else if (3 == iPlayerSelect)
			{
				*nextBranch = iPlayerSelect;
				GameSystem::GetInstance()->PlayerInit(iPlayerSelect);
				break;
			}
			else if (4 == iPlayerSelect)
			{
				*nextBranch = iPlayerSelect;
				GameSystem::GetInstance()->PlayerInit(iPlayerSelect);

				break;
			}
			else
			{
				std::cout << "�߸��� ������ �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� !!" << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			//
		}
		else if (type == eScene::SCENE_VILLAGE)
		{
			if (2 == iPlayerSelect)
			{
				*nextBranch = iPlayerSelect;
				break;
			}
			else if (3 == iPlayerSelect)
			{
				*nextBranch = iPlayerSelect;
				break;
			}
			else
			{
				std::cout << "�߸��� ������ �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� !!" << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}
		else if (type == eScene::SCENE_DUNGEON)
		{
			if (1 == iPlayerSelect)
			{
				*nextBranch = iPlayerSelect;
				break;

			}
			else if (2 == iPlayerSelect)
			{
				*nextBranch = iPlayerSelect;
				break;

			}
			else if (3 == iPlayerSelect)
			{
				*isQuit = true;
				break;
			}
			else if (std::cin.fail())
			{
				std::cout << "�߸��� ������ �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� !!" << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			else
			{
				std::cout << "�߸��� ������ �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� !!" << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}
	}

	std::cin.clear();
	std::cin.ignore();
}
