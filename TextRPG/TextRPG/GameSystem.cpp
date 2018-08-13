#include "GameSystem.h"

#include <iostream>
#include <conio.h>
#include <ostream>
#include <fstream>

#include "ParsingSystem.h"
#include "Player.h"

GameSystem* GameSystem::_instance = 0;

GameSystem::GameSystem()
{
	iPlayerSelect = 0;
}


GameSystem::~GameSystem()
{
}

GameSystem* GameSystem::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new GameSystem();
	}
	return _instance;
}

void GameSystem::InitPosen(Character* _player)
{
	
	std::list<std::pair< std::string, int>> listIventory = _player->GetInventory();

	std::list<std::pair< std::string, int>>::iterator iter;
	std::list<std::pair< std::string, int>>::iterator iterBegin = listIventory.begin();
	std::list<std::pair< std::string, int>>::iterator iterEnd = listIventory.end();


	std::vector<sData>::iterator itPosen;

	for (iter = iterBegin; iter != iterEnd; iter++)
	{
		for (itPosen = vRecveryInfo.begin(); itPosen != vRecveryInfo.end(); itPosen++)
		{
			if (iter->first == itPosen->sNameInfo)
			{
				lPoseonInventory.push_back(*itPosen);
			}
		}

	}
	

}

void GameSystem::CharacterCreate(eCharacterType type)
{
	switch (type)
	{
	case eCharacterType::PLAYER:
		_character = new Player();
		break;
	}
}

void GameSystem::PlayerInit(int _number)
{
	_character->Init(_number);
}

void GameSystem::SetPlayerName(std::string _name)
{
	_character->SetName(_name);
}

void GameSystem::InitItemInfo()
{
	_parser = new ParsingSystem();

	_parser->ItemTableCSVParsing("RecoveryItemTable.csv", &vRecveryInfo);
	_parser->ItemTableCSVParsing("ArmsItemTable.csv", &vArmsInfo);
	_parser->ItemTableCSVParsing("DefensiveItemTable.csv", &vDefensiveInfo);

}


void GameSystem::FindinventoryInfoView(std::list<std::pair<std::string, int>>* vInventory, int _iSelect, sEquipment* _eq)
{
	std::list<std::pair<std::string, int>>::iterator it;
	std::vector<sData>::iterator iter;

	int i = 1;
	bool isWear = false;
	std::cout << "======��ȣ=====�����۸�=============����====" << std::endl;

	switch (_iSelect)
	{
	case 1:
		for (it = vInventory->begin(); it != vInventory->end(); it++, i++)
		{
			// vRecveryInfo
			for (iter = vRecveryInfo.begin(); iter != vRecveryInfo.end(); iter++)
			{
				if (it->first == iter->sNameInfo)
				{
					std::cout << " [ ��ȣ : " << i << " ] " << " [ �̸� : " << it->first << " ] " << 
						" [ HP ȸ�� : " << iter->iHpInfo << " ] " << " [ ���� ȸ�� :" << iter->iMpInfo << " ] " <<
						" [ ������ : " << iter->iLevelUpInfo << " ] " << " [ ���� : " << iter->sTextInfo << " ] " << std::endl;
				}
			}
		}
		break;
	case 2:
		for (it = vInventory->begin(); it != vInventory->end(); it++, i++)
		{

			// vArmsInfo
			for (iter = vArmsInfo.begin(); iter != vArmsInfo.end(); iter++)
			{
				if (it->first == iter->sNameInfo)
				{
					if (it->first == iter->sNameInfo)
					{
						std::cout << " [ ��ȣ : " << i << " ] " << " [ �̸� : " << it->first << " ] "  <<
							" [ ���ݷ� : " << iter->iAttackPointInfo << " ] " << " [ ���� :" << iter->iDefensiveInfo << " ] " <<
							" [ ���� ���� : " << iter->iLvInfo << " ] " << " [ ���� : " << iter->sTextInfo << " ] " << std::endl;
					}
				}
			}

		}
		break;
	case 3:
		for (it = vInventory->begin(); it != vInventory->end(); it++, i++)
		{
			// vDefensiveInfo
			for (iter = vDefensiveInfo.begin(); iter != vDefensiveInfo.end(); iter++)
			{
				if (it->first == iter->sNameInfo)
				{
					if (it->first == iter->sNameInfo)
					{
						std::cout << " [ ��ȣ : " << i << " ] " << " [ �̸� : " << it->first << " ] "  <<
							" [ �� : " << iter->iStrInfo << " ] " << " [ ��ø : " << iter->iDexInfo << " ] " <<
							" [ ���� : " << iter->iIntInfo << " ] " << " [ ���� : " << iter->sTextInfo << " ] " << std::endl;
					}
				}
			}
		}
		break;
	}

	system("pause");
	std::string sName;
	bool _isQuit = false;



	if (2 == _iSelect)
	{
		while (false == _isQuit)
		{
			std::cout << "��� �����Ͻðڽ��ϱ�? ( y / n) : ";
			std::cin >> chText;
			if ('y' == chText || 'Y' == chText)
			{
				std::cout << "--------------------------------" << std::endl;
				std::cout << "�κ� �丮 �� �ִ� ������ �Է��� �ּ��� : ";
				std::cin >> sName;
				for (it = vInventory->begin(); it != vInventory->end(); it++)
				{
					for (iter = vArmsInfo.begin(); iter != vArmsInfo.end(); iter++)
					{
						if (it->first == iter->sNameInfo)
						{
							if (sName == it->first)
							{
								if (_character->GetLv() >= iter->iLvInfo)
								{
									if (true == isWear)
									{
										_character->ChangeWear(_eq, sName, _iSelect);
										_character->ChangeWearState(iter->iAttackPointInfo, iter->iDefensiveInfo, iter->iStrInfo, iter->iDexInfo, iter->iIntInfo);
										break;
									}
									else
									{
										isWear = true;
										_character->CharacterWear(_eq, sName, _iSelect);
										_character->ChangeWearState(iter->iAttackPointInfo, iter->iDefensiveInfo, iter->iStrInfo, iter->iDexInfo, iter->iIntInfo);
										break;
									}

								}
								else if(_character->GetLv() <= iter->iLvInfo)
								{
									std::cout << "������ ������ ������ �Ұ��� �մϴ�...." << std::endl;
									_getch();
									break;
								}
							}
						}
					}
				}
				_isQuit = true;

			}
			else if ('n' == chText || 'N' == chText)
			{
				_isQuit = true;
				break;
			}
			else
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				StdCinClear();

				continue;
			}
		}
	}
	else if (3 == _iSelect)
	{
		while (false == _isQuit)
		{
			std::cout << "��� �����Ͻðڽ��ϱ�? ( y / n) : ";
			std::cin >> chText;
			if ('y' == chText || 'Y' == chText)
			{
				std::cout << "--------------------------------" << std::endl;
				std::cout << "�κ� �丮 �� �ִ� ������ �Է��� �ּ��� : ";
				std::cin >> sName;
				for (it = vInventory->begin(); it != vInventory->end(); it++)
				{
					for (iter = vDefensiveInfo.begin(); iter != vDefensiveInfo.end(); iter++)
					{
						if (it->first == iter->sNameInfo)
						{
							if (sName == it->first)
							{
								if (true == isWear)
								{
									_character->ChangeWear(_eq, sName, _iSelect);
									_character->ChangeWearState(iter->iAttackPointInfo, iter->iDefensiveInfo, iter->iStrInfo, iter->iDexInfo, iter->iIntInfo);
									break;
								}
								else
								{
									isWear = true;
									_character->CharacterWear(_eq, sName, _iSelect);
									_character->ChangeWearState(iter->iAttackPointInfo, iter->iDefensiveInfo, iter->iStrInfo, iter->iDexInfo, iter->iIntInfo);
									break;
								}

							}
						}
					}
				}
			}
			else if ('n' == chText || 'N' == chText)
			{
				_isQuit = true;
				break;
			}
			else
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				StdCinClear();

				continue;
			}
		}
	}
	system("cls");
}

void GameSystem::CollisionEvent(Character* _player, Character* _monster, int _rand, int* nextBranch, bool* isQuit)
{
	if (0 == _rand)
	{
		std::cout << "�ƹ��� ������ �ʾҴ�. ! �����ߴ�.." << std::endl;
		return;
	}
	
	std::cout << _monster->GetName() << " �� �������ϴ�! " << std::endl;
	std::cout << "================= Monster ================" << std::endl;
	std::cout << "�̸� : " << _monster->GetName() << std::endl;
	std::cout << "ü�� : " << _monster->GetHp() << std::endl;
	std::cout << "���ݷ� : " << _monster->GetAttackPoint() << std::endl;
	std::cout << "���� : " << _monster->GetDefensePoint() << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << "------------------------------------------" << std::endl;
	std::cout << "================= Player ================" << std::endl;
	std::cout << "====================================" << std::endl;
	std::cout << "���� : " << _player->GetLv() << std::endl;
	std::cout << "ü�� : " << _player->GetHp() << std::endl;
	std::cout << "���ݷ� : " << _player->GetAttackPoint() << std::endl;
	std::cout << "���� : " << _player->GetDefensePoint() << std::endl;
	std::cout << "====================================" << std::endl;

	while (1)
	{

		std::cout << _monster->GetName() << " �� ������ �Ͻðڽ��ϱ�? ( Y / N )  " << std::endl;
		std::cin >> chText;
		if ('y' == chText || 'Y' == chText)
		{
			// ����
			Battle(_player, _monster, nextBranch, isQuit);
			break;
			*nextBranch = 4;
		}
		else if ('n' == chText || 'N' == chText)
		{
			*nextBranch = 0;
			break;
		}
	}
	system("cls");

}


void GameSystem::Battle(Character* _player, Character* _monster, int* nextBranch, bool* isQuit)
{
	system("cls");
	int iPlayerHp = _player->GetHp();
	bool isBattle = true;
	while (true == isBattle)
	{
		// �ൿ 
		std::cout << "================= Monster ================" << std::endl;
		std::cout << "�̸� : " << _monster->GetName() << std::endl;
		std::cout << "ü�� : " << _monster->GetHp() << std::endl;
		std::cout << "���ݷ� : " << _monster->GetAttackPoint() << std::endl;
		std::cout << "���� : " << _monster->GetDefensePoint() << std::endl;
		std::cout << "====================================" << std::endl;
		std::cout << "------------------------------------------" << std::endl;
		std::cout << "================= Plaer ================" << std::endl;
		std::cout << "====================================" << std::endl;
		std::cout << "���� : " << _player->GetLv() << std::endl;
		std::cout << "ü�� : " << _player->GetHp() << std::endl;
		std::cout << "���ݷ� : " << _player->GetAttackPoint() << std::endl;
		std::cout << "���� : " << _player->GetDefensePoint() << std::endl;
		std::cout << "====================================" << std::endl;

		std::cout << "1. ���� , 2. ��ų , 3. ���� , 4. �������� ";
		std::cin >> iPlayerSelect;
		int iSkillDamage = 0;
		switch (iPlayerSelect)
		{
		case 1:
			{
				if (_player->GetDex() > (_monster->GetAttackPoint() / 10))
				{
					// Skill 
					std::cout << "�÷��̾ ���� ! " << std::endl;
					_monster->DecreaseHP(_player->GetAttackPoint());
					_getch();

					if (_monster->GetHp() <= 0)
					{
						_player->IncreaseExp(_monster);
						std::cout << "�÷��̾ �¸� �Ͽ����ϴ�.." << std::endl;
						_getch();
						isBattle = false;
						break;
					}

					if (_player->GetHp() <= 0)
					{
						_player->Reset(iPlayerHp);
						std::cout << "�÷��̾ �й� �Ͽ����ϴ�.." << std::endl;
						_getch();
						*nextBranch = 11;
						isBattle = false;
						break;

					}
					std::cout << "���Ͱ� ���� ! " << std::endl;
					_player->DecreaseHP(_monster->GetAttackPoint());
					_getch();

					
				}
				else
				{

					std::cout << "���Ͱ� ���� ! " << std::endl;
					_player->DecreaseHP(_monster->GetAttackPoint());
					_getch();

					if (_player->GetHp() <= 0)
					{
						_player->Reset(iPlayerHp);
						std::cout << "�÷��̾ �й� �Ͽ����ϴ�.." << std::endl;
						*nextBranch = 11;
						_getch();
						isBattle = false;
						break;

					}
					std::cout << "�÷��̾ ���� ! " << std::endl;
					_monster->DecreaseHP(_player->GetAttackPoint());
					_getch();

					if (_monster->GetHp() <= 0)
					{
						std::cout << "�÷��̾ �¸� �Ͽ����ϴ�.." << std::endl;
						_getch();
						isBattle = false;
						break;

					}
				}
			}
		break;
		case 2:
		{
			int iSelectSkill = _player->Skill();

			if (4 == iSelectSkill)
			{
				break;
			}
			else
			{
				iSkillDamage = _player->SkillDamge(iSelectSkill);
			}

			if (_player->GetDex() > (_monster->GetAttackPoint() / 10))
			{
				_monster->DecreaseHP(_player->GetAttackPoint() + iSkillDamage);
				_getch();

				if (_monster->GetHp() <= 0)
				{
					_player->IncreaseExp(_monster);
					std::cout << "�÷��̾ �¸� �Ͽ����ϴ�.." << std::endl;
					_getch();

					isBattle = false;
					break;

				}
				_player->DecreaseHP(_monster->GetAttackPoint());
				_getch();

				if (_player->GetHp() <= 0)
				{
					_player->Reset(iPlayerHp);
					std::cout << "�÷��̾ �й� �Ͽ����ϴ�.." << std::endl;
					_getch();

					*nextBranch = 11;
					isBattle = false;
					break;

				}
			}
			else
			{
				_player->DecreaseHP(_monster->GetAttackPoint());
				_getch();

				if (_player->GetHp() <= 0)
				{
					_player->Reset(iPlayerHp);
					std::cout << "�÷��̾ �й� �Ͽ����ϴ�.." << std::endl;
					_getch();

					*nextBranch = 11;
					isBattle = false;
					break;

				}
				_monster->DecreaseHP(_player->GetAttackPoint() + iSkillDamage);
				_getch();

				if (_monster->GetHp() <= 0)
				{
					std::cout << "�÷��̾ �¸� �Ͽ����ϴ�.." << std::endl;
					_getch();

					isBattle = false;
					break;

				}
			}
		}
		break;

		case 3:
			_player->DrinkingPoseon();
			break;

		case 4:
			isBattle = false;
			std::cout << "���������ϴ�.." << std::endl;
			_getch();

			break;

		default:
			std::cout << "�߸��� ���� �Է� �߽��ϴ�. �ٽ� �Է��� �ּ��� .." << std::endl;
			StdCinClear();

			break;
		}
		
		system("cls");
	}
	
}

void GameSystem::Save(Character* _player)
{
	system("cls");
	std::cout << "�����߽��ϴ�!!" << std::endl;
	system("pause");

	std::ofstream outFile("Player.dat", std::ofstream::out | std::ios::trunc);
	outFile << "Name,Job,Lv,Hp,Mp,AttackPoint,DefPoint,Str,Dex,Int,Gold" << std::endl;
	outFile << _player->GetName() << "," << _player->GetjobType()<< "," << _player->GetLv() << "," << 
		_player->GetHp()<<","<< _player->GetMp() << "," <<_player->GetAttackPoint() << ","
		<< _player->GetDefensePoint() << "," << _player->GetStr() << "," << _player->GetDex() << "," <<
		_player->GetInt() << "," << _player->GetGold();
	outFile.close();
	system("cls");

}

void GameSystem::Load(bool* _isLoad)
{
	Character* _player = GetCharacter();
	_parser->PlayerParsing("Player.dat", _player, _isLoad);

}

void GameSystem::StdCinClear()
{
	std::cin.clear();
	std::cin.ignore();
}

void GameSystem::Release()
{
	delete _character;
	delete _instance;
}
