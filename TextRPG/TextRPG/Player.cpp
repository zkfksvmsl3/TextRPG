#include "Player.h"

#include <iostream>


Player::Player()
{
	// �ʱ�ȭ 
	iPlayerSelect = 0;
	iGold = 1000;
	iInvenSize = 0;
	iStatePoint = 10;
	jobType = eJobType::NONE;
	iExp = GetLv() * 1000 + GetStr() + GetDex() + GetInt();

	eq = new sEquipment();
}


Player::~Player()
{
}

void Player::SetName(std::string _name)
{
	sPlayerName = _name;
}

void Player::Init(int _number)
{
	// ���� �ʱ�ȭ 
	switch ((eJobType)_number)
	{
	case eJobType::WARRIOR:
		WarriorInit(eJobType::WARRIOR);
		break;
	case eJobType::ARCHER:
		ArcherInit(eJobType::ARCHER);
		break;
	case eJobType::WIZARD:
		WizardInit(eJobType::WIZARD);
		break;
	}
}

void Player::WarriorInit(eJobType type)
{
	jobType = type;
	iLv = 1;
	iStr = 10;
	iDex = 5;
	iInt = 5;
}

void Player::ArcherInit(eJobType type)
{
	jobType = type;
	iLv = 1;
	iStr = 5;
	iDex = 10;
	iInt = 5;
}

void Player::WizardInit(eJobType type)
{
	jobType = type;
	iLv = 1;
	iStr = 5;
	iDex = 5;
	iInt = 10;
}

void Player::AddInventory(std::list<Item>::iterator& it)
{
	 // �κ��丮 �߰� ( 30 ���� ����)  
	if (iInvenSize > 30)
	{
		std::cout << " ������ ũ�⸦ �ʰ� �߽��ϴ�! " << std::endl;
		return;
	}
	else
	{
		std::pair<std::string,int> pKey;
		pKey.first = it->sItemName;
		pKey.second = it->iPrice /2;
		vInventory.push_back(pKey);
		iInvenSize++;

		//
	}
	
}

void Player::InventoryView()
{
	std::list<std::pair<std::string,int>>::iterator it;
	int i = 1;
	std::cout << "======��ȣ==�����۸�====����=======" << std::endl;
	for (it = vInventory.begin(); it != vInventory.end(); it++,i++)
	{
		std::cout << i << "\t" << it->first << "\t" << it->second << std::endl;
	}
	system("pause");
}

void Player::InventoryInfoView(int _iSelect, sEquipment* _eq)
{
	{
		GameSystem::GetInstance()->FindinventoryInfoView(&vInventory, _iSelect, _eq);
	}
}

void Player::InventoryPoseonView()
{
	{
		std::list<sData> lPosean = GameSystem::GetInstance()->GetPoseonInventory();
		std::list<sData>::iterator it;
		std::list<sData>::iterator itBegin = lPosean.begin();
		std::list<sData>::iterator itEnd = lPosean.end();

		int i = 1;
		for (it = itBegin; it != itEnd; it++,i++)
		{
			std::cout << "[ ��ȣ : " << i << " ]" << "   " <<
				" [  �����۸� : " << it->sNameInfo << " ] " << "   " <<
				" [  HP ȸ�� : " << it->iHpInfo << " ] " << "   " <<
				" [  MP ȸ�� : " << it->iMpInfo << " ] " << "   " <<
				" [  ������  : " << it->iLevelUpInfo << " ] " << std::endl;
		}

	
	}
}


int Player::GetInventorySize()
{
	return vInventory.size();
}

int Player::DeleteInventoryItem(int iPlayerSelect)
{
	if (0 == vInventory.size())
	{
		std::cout << " �ƹ��͵� �����ϴ�! " << std::endl;
		return 0;
	}
	std::list<std::pair<std::string, int>>::iterator it;
	std::list<std::pair<std::string, int>>::iterator iter;

	int iGold;
	int iIndex = 1;
	for (it = vInventory.begin(); it != vInventory.end(); it++,iIndex++)
	{
		if (0 == vInventory.size())
		{
			break;
		}

		if (iPlayerSelect == iIndex)
		{
			iGold = it->second;
			iter = it;
			it = vInventory.erase(iter);
			break;
		}

		if (0 == vInventory.size())
		{
			break;
		}
		
	}
	iIndex = 0;
	InventoryView();

	return iGold;
}

int Player::DeleteInventoryItem(std::string _name)
{
	if (0 == vInventory.size())
	{
		std::cout << " �ƹ��͵� �����ϴ�! " << std::endl;
		return 0;
	}
	std::list<std::pair<std::string, int>>::iterator it;
	int iIndex = 1;
	for (it = vInventory.begin(); it != vInventory.end(); it++, iIndex++)
	{
		if (0 == vInventory.size())
		{
			break;
		}

		if (it->first == _name )
		{
			vInventory.pop_back();
			break;
		}
		

	}

	return 0;
}

void Player::PlayerState()
{
	system("cls");

	std::cout << "=======================================" << std::endl;
	
	// ĳ���� ����
	
	bool isQuit = false;
	while (false == isQuit)
	{
		std::cout << "1. ĳ���� ���� / 2. ĳ���� ��� / 3. ĳ���� ���� / 4. ���ư���" << std::endl;
		std::cout << "���ڸ� �Է��� �ּ��� : ";
		std::cin >> iPlayerSelect;
		
		switch (iPlayerSelect)
		{
		case 1:
			CharacterInfo();
			break;
		case 2:
			CharacterEquipment(eq);
			break;
		case 3:
			CharacterInventory(eq);
			break;
		case 4:
			system("cls");
			isQuit = true;
			break;
		default:
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
			GameSystem::GetInstance()->StdCinClear();
		}
	}
}

void Player::CharacterInfo()
{
	system("cls");

	Update();
	std::cout << "=======================================" << std::endl;
	std::cout << "PlayerName : " << sPlayerName <<std::endl;
	switch (GetjobType())
	{
	case eJobType::WARRIOR:
		std::cout << "       JOB : " << " �� �� " << std::endl;
		break;
	case eJobType::ARCHER:
		std::cout << "       JOB : " << " �� �� " << std::endl;
		break;
	case eJobType::WIZARD:
		std::cout << "       JOB : " << " �� �� �� " << std::endl;
		break;
	}
	std::cout << "        Lv : " << GetLv() << std::endl;
	std::cout << "        HP : " << GetHp() << std::endl;
	std::cout << "        MP : " << GetMp() << std::endl;
	std::cout << "    ATTACK : " << GetAttackPoint() << std::endl;
	std::cout << "   DEFENSE : " << GetDefensePoint() << std::endl;
	std::cout << "       STR : " << GetStr() << std::endl;
	std::cout << "       DEX : " << GetDex() << std::endl;
	std::cout << "       INT : " << GetInt() << std::endl;
	std::cout << "=======================================" << std::endl;
	std::cout << "StatePoint : " << GetStatePoint()<<std::endl;
	std::cout << "=======================================" << std::endl;
	
	system("pause");
	
	if (0 == GetStatePoint())
	{
		return;
	}
	else
	{
		while (1)
		{

			std::cout << "��������Ʈ�� " << GetStatePoint() << " �ֽ��ϴ�.. ������ ��ڽ��ϱ�?? ( y / n )" << std::endl;
			std::cin >> chText;

			if ('y' == chText || 'Y' == chText)
			{
				StateUp();
			}
			else if ('n' == chText || 'N' == chText)
			{
				break;
			}

			if (0 == GetStatePoint())
			{
				std::cout << "����Ʈ�� �����ϴ�!" << std::endl;
				break;
			}
		}
	}

	system("cls");

}

void Player::CharacterEquipment(sEquipment* _eq)
{
	// ���â
	system("cls");
	std::cout << "----��----" << std::endl;
	std::cout << " ��    �� : " << " [ "<<_eq->sHeadGear << " ] " << std::endl;
	std::cout << " ��    �� : " << " [ " << _eq->sChestGear << " ] " << std::endl;
	std::cout << " ��    �� : " << " [ " << _eq->sPantsGear << " ] " << std::endl;
	std::cout << " ��   ��  : " << " [ " <<_eq->sShoesGear << " ] " << std::endl;
	std::cout << "----��  ��----" << std::endl;
	std::cout << " �� �� �� : " << " [ " << _eq->sRighthandGear << " ] " << std::endl;
	std::cout << " ��    �� : " << " [ " << _eq->sLeftHandGear << " ] " << std::endl;
	system("pause");
	system("cls");
}

void Player::CharacterInventory(sEquipment* _eq)
{
	// �κ��丮 â 
	system("cls");

	if (0 == GetInventorySize())
	{
		std::cout << "�ƹ� �͵� �����ϴ�.." << std::endl;
		system("pause");
		system("cls");
		return;
	}
	

	while (1)
	{
		std::cout << "=======================================" << std::endl;
		std::cout << "1. �Ҹ�ǰ , 2. ���� , 3. ��� : , 4. ������ " << std::endl;
		std::cout << "=======================================" << std::endl;

		std::cout << "��� �������� �̵� �Ͻðڽ��ϱ�?";
		std::cin >> iPlayerSelect;

		if (1 == iPlayerSelect)
		{
			InventoryInfoView(iPlayerSelect, _eq);
		}
		else if (2 == iPlayerSelect)
		{
			InventoryInfoView(iPlayerSelect, _eq);
		}
		else if (3 == iPlayerSelect)
		{
			InventoryInfoView(iPlayerSelect, _eq);
		}
		else if (4 == iPlayerSelect)
		{
			break;
		}
		else if (std::cin.fail())
		{
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}
		else
		{
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}
	}

	system("cls");

}

void Player::StateUp()
{
	system("cls");

	int iPointUp;

	int iStrPoint;
	int iDexPoint;
	int iIntPoint;
	int iPoint;

	while (1)
	{
		std::cout <<"���� ��������Ʈ ! : "<< GetStatePoint()<< std::endl;
		std::cout << "1. �� / 2. ��ø / 3. ���� " << std::endl;
		std::cout << "������� ����Ʈ�� �ø��ڽ��ϱ�? :" ;
		std::cin >> iPlayerSelect;

		
		if(1 == iPlayerSelect)
		{
			std::cout << "�� ����Ʈ�� �ø��ڽ��ϱ�? :";
			std::cin >> iPointUp;

			if (GetStatePoint() < iPointUp || std::cin.fail())
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			else
			{
				iStrPoint = GetStr();
				iStrPoint = iStrPoint + iPointUp;
				SetStr(iStrPoint);
				iPoint = GetStatePoint() - iPointUp;
				SetStatePoint(iPoint);
			}
			
		}
		else if (2 == iPlayerSelect)
		{
			std::cout << "�� ����Ʈ�� �ø��ڽ��ϱ�? :";
			std::cin >> iPointUp;

			
			if (GetStatePoint() < iPointUp || std::cin.fail())
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			else
			{
				iDexPoint = GetDex();
				iDexPoint = iDexPoint + iPointUp;
				SetDex(iDexPoint);
				iPoint = GetStatePoint() - iPointUp;
				SetStatePoint(iPoint);
			}
		}
		else if (3 == iPlayerSelect)
		{
			std::cout << "�� ����Ʈ�� �ø��ڽ��ϱ�? :";
			std::cin >> iPointUp;

			if (GetStatePoint() < iPointUp || std::cin.fail())
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			else
			{
				iIntPoint = GetInt();
				iIntPoint = iIntPoint + iPointUp;
				SetInt(iIntPoint);
				iPoint = GetStatePoint() - iPointUp;
				SetStatePoint(iPoint);
			}
		}
		else
		{
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}
		// ���� �ʱ�ȭ 
		if (0 == GetStatePoint())
		{
			break;
		}
	}
}

void Player::CharacterWear(sEquipment* _eq, std::string sName, int _iSelect)
{

	int iHandSelect;
	if (2 == _iSelect)
	{
		while (1)
		{
			std::cout << "1. ������ / 2. �޼� " << std::endl;
			std::cin >> iHandSelect;

			if (1 == iHandSelect)
			{

				if (false == _eq->IsRighthandGear)
				{
					_eq->sRighthandGear = sName;
					_eq->IsRighthandGear = true;
					break;
				}
			}
			else if (2 == iHandSelect)
			{
				if (false == _eq->IsLeftHandGear)
				{
					_eq->sLeftHandGear = sName;
					_eq->IsRighthandGear = true;
					break;
				}
			}
			else if (std::cin.fail())
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			else
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}
		
	}
	else if (3 == _iSelect)
	{
		if (false == _eq->IsHeadGear)
		{
			_eq->sHeadGear = sName;
			_eq->IsHeadGear = true;

		}
		else if (false == _eq->IsChestGear)
		{
			_eq->sChestGear = sName;
			_eq->IsChestGear = true;
		}
		else if (false == _eq->IsPantsGear)
		{
			_eq->sPantsGear = sName;
			_eq->IsPantsGear = true;
		}
		else if (false == _eq->IsShoesGear)
		{
			_eq->sShoesGear = sName;
			_eq->IsShoesGear = true;
		}
	}
	
}

void Player::ChangeWear(sEquipment* _eq, std::string sName, int _iSelect)
{

	if (2 == _iSelect)
	{
		while (1)
		{
			std::cout << "1. ������ / 2. �޼� " << std::endl;
			std::cin >> iPlayerSelect;

			if (1 == iPlayerSelect)
			{
				if (true == _eq->IsRighthandGear)
				{
					DeleteInventoryItem(_eq->sRighthandGear);

					_eq->sRighthandGear = sName;
					_eq->IsRighthandGear = true;
					break;
				}
			}
			else if (2 == iPlayerSelect)
			{
				if (true == _eq->IsLeftHandGear)
				{
					DeleteInventoryItem(_eq->sLeftHandGear);

					_eq->sLeftHandGear = sName;
					_eq->IsRighthandGear = true;
					break;
				}
			}
			else if (std::cin.fail())
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			else
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}

	}
	else if (3 == _iSelect)
	{
		if (true == _eq->IsHeadGear)
		{
			DeleteInventoryItem(_eq->sHeadGear);

			_eq->sHeadGear = sName;
			_eq->IsHeadGear = true;

		}
		else if (true == _eq->IsChestGear)
		{
			DeleteInventoryItem(_eq->sChestGear);

			eq->sChestGear = sName;
			eq->IsChestGear = true;
		}
		else if (true == _eq->IsPantsGear)
		{
			DeleteInventoryItem(_eq->sPantsGear);

			_eq->sPantsGear = sName;
			_eq->IsPantsGear = true;
		}
		else if (true == _eq->IsShoesGear)
		{
			DeleteInventoryItem(_eq->sShoesGear);

			_eq->sShoesGear = sName;
			_eq->IsShoesGear = true;
		}
	}
}

void Player::ChangeWearState(int iAttackPointInfo, int iDefensiveInfo, int iStrInfo, int iDexInfo, int iIntInfo)
{
	SetAttackPoint(GetAttackPoint() + iAttackPointInfo);
	SetDefensePoint(GetDefensePoint() + iDefensiveInfo);
	SetStr(GetStr() + iStrInfo);
	SetDex(GetDex() + iDexInfo);
	SetInt(GetInt() + iIntInfo);

}

void Player::Update()
{
	switch (GetjobType())
	{
	case eJobType::WARRIOR:
		WarriorStateUpdate();
		break;
	case eJobType::ARCHER:
		ArcherStateUpdate();
		break;
	case eJobType::WIZARD:
		WizardStateUpdate();
		break;
	}
	
}

void Player::WarriorStateUpdate()
{
	int iAttack = GetAttackPoint() + GetStr() * GetLv();
	int iHp = GetHp() + GetStr() + 10;
	int iMp = GetMp() + GetInt();
	SetMaxHp(iHp);
	SetMaxMp(iMp);
	SetAttackPoint(iAttack);
	SetHp(iHp);
	SetMp(iMp);

}

void Player::ArcherStateUpdate()
{
	int iAttack = GetAttackPoint() + (GetDex()/2) * GetLv();
	int iDef = GetDefensePoint() + ((GetDex() / 5) + 2);
	int iHp = GetHp() + GetStr() + 3;
	int iMp = GetMp() + GetInt();
	SetMaxHp(iHp);
	SetMaxMp(iMp);
	SetAttackPoint(iAttack);
	SetDefensePoint(iDef);
	SetHp(iHp);
	SetMp(iMp);
}

void Player::WizardStateUpdate()
{
	int iAttack = GetAttackPoint() + (GetInt()/3) * GetLv();
	int iHp = GetHp() + GetStr() + 3;
	int iMp = GetMp() + GetInt() +10;
	SetMaxHp(iHp);
	SetMaxMp(iMp);
	SetAttackPoint(iAttack);
	SetHp(iHp);
	SetMp(iMp);
}

void Player::DecreaseHP(int _attackPoint)
{
	SetHp(GetHp() - _attackPoint);

	if (GetHp() <= 0)
	{
		SetHp(0);
	}
}

void Player::Reset(int _hp)
{
	SetHp(_hp);
}

void Player::IncreaseExp(Character* _monster)
{
	int iExpLine = GetExp();
	iExpLine -= _monster->GetExp();

	if (0 >= iExpLine)
	{
		LevelUp();
	}

}

void Player::LevelUp()
{
	SetLv(GetLv() + 1);
	iStatePoint = iStatePoint + 5;
}

int Player::Skill()
{
	if (GetjobType() == eJobType::WARRIOR)
	{
		std::cout << "1. ���Ž�! ( �� x ���ݷ� , ���� 10 ) " << std::endl;
		std::cout << "2. �ʻ� ���Ž� ! ( �� x ���ݷ� + 50 , ���� 50 )  " << std::endl;
		std::cout << "3. �ñ� ���Ž� ! ( �� x ���ݷ� + 500  , ���� 100)  " << std::endl;
		std::cout << "4. ������ " << std::endl;
		std::cout << "���� MP : " << GetMp() << std::endl;
		while (1)
		{
			std::cout << "� ��ų�� ����Ͻðڽ��ϱ�? ( 1 ~4 ) :";
			std::cin >> iPlayerSelect;

			if (1 == iPlayerSelect)
			{
				if (10 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.."<< std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (2 == iPlayerSelect)
			{
				if (50 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (3 == iPlayerSelect)
			{
				if (100 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (4 == iPlayerSelect)
			{
				std::cout << "����â���� �̵� �մϴ�." << std::endl;
				break;
			}
			else
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ���! " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}
	}
	else if (GetjobType() == eJobType::ARCHER)
	{
		std::cout << "1. �Ŀ���! ( �� x ���ݷ� , ���� 10 ) " << std::endl;
		std::cout << "2 .�ʻ� �Ŀ��� ! ( �� x ���ݷ� + 50 , ���� 50 )  " << std::endl;
		std::cout << "3. �ñ� �Ŀ��� ! ( �� x ���ݷ� + 500  , ���� 100)  " << std::endl;
		std::cout << "4. ������ " << std::endl;
		std::cout << "���� MP : " << GetMp() << std::endl;
		while (1)
		{
			std::cout << "� ��ų�� ����Ͻðڽ��ϱ�? ( 1 ~4 ) :";
			std::cin >> iPlayerSelect;

			if (1 == iPlayerSelect)
			{
				if (10 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (2 == iPlayerSelect)
			{
				if (50 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (3 == iPlayerSelect)
			{
				if (100 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (4 == iPlayerSelect)
			{
				std::cout << "����â���� �̵� �մϴ�." << std::endl;
				break;
			}
			else
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ���! " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}
	}
	else if (GetjobType() == eJobType::WIZARD)
	{

		std::cout << "1. ���̾! ( �� x ���ݷ� , ���� 10 ) " << std::endl;
		std::cout << "2 . ���̽���! ( �� x ���ݷ� + 50 , ���� 50 )  " << std::endl;
		std::cout << "3. ���׿� ! ( �� x ���ݷ� + 500 , ���� 100)  " << std::endl;
		std::cout << "4. ������ " << std::endl;
		std::cout << "���� MP : " << GetMp() << std::endl;
		while (1)
		{
			std::cout << "� ��ų�� ����Ͻðڽ��ϱ�? ( 1 ~4 ) :";
			std::cin >> iPlayerSelect;

			if (1 == iPlayerSelect)
			{
				if (10 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;
			}
			else if (2 == iPlayerSelect)
			{
				if (50 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (3 == iPlayerSelect)
			{
				if (100 > GetMp())
				{
					std::cout << "������ ���� �մϴ�.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (4 == iPlayerSelect)
			{
				std::cout << "����â���� �̵� �մϴ�." << std::endl;
				break;
			}
			else
			{
				std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ���! " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}
	}

	return iPlayerSelect;
	
}

int Player::SkillDamge(int iSelectSkill)
{
	int iSkillDamage = 0;

	if (GetjobType() == eJobType::WARRIOR)
	{
		if (1 == iSelectSkill)
		{
			std::cout << "1. ���Ž�! ~ �ߵ�!" << std::endl;

			SetMp(GetMp() - 10);
			iSkillDamage = GetAttackPoint() * GetStr();
		}
		else if (2 == iSelectSkill)
		{
			std::cout << "2. �ʻ� ���Ž� ! ~ �ߵ�!  " << std::endl;
			SetMp(GetMp() - 50);
			iSkillDamage = GetAttackPoint() * GetStr() + 50;

		}
		else if (3 == iSelectSkill)
		{
			std::cout << "3. �ñ� ���Ž� !  ~ �ߵ�! " << std::endl;
			SetMp(GetMp() - 100);
			iSkillDamage = GetAttackPoint() * GetStr() + 500;
		}
	}
	else if (GetjobType() == eJobType::ARCHER)
	{
		if (1 == iSelectSkill)
		{
			std::cout << "1. �Ŀ���! ~ �ߵ� !" << std::endl;
			SetMp(GetMp() - 10);
			iSkillDamage = GetAttackPoint() * GetDex();
		}
		else if (2 == iSelectSkill)
		{
			std::cout << "2 .�ʻ� �Ŀ��� !  ~ �ߵ� !  " << std::endl;
			SetMp(GetMp() - 50);
			iSkillDamage = GetAttackPoint() * GetDex() + 50;

		}
		else if (3 == iSelectSkill)
		{

			std::cout << "3. �ñ� �Ŀ��� !  ~ �ߵ� !  " << std::endl;
			SetMp(GetMp() - 100);
			iSkillDamage = GetAttackPoint() * GetDex() + 500;
		}
	}
	else if (GetjobType() == eJobType::WIZARD)
	{
		if (1 == iSelectSkill)
		{
			std::cout << "1. ���̾ ~ �ߵ� ! " << std::endl;
			SetMp(GetMp() - 10);
			iSkillDamage = GetAttackPoint() * GetInt();
		}
		else if (2 == iSelectSkill)
		{
			std::cout << "2 . ���̽��� ~ �ߵ� ! " << std::endl;
			SetMp(GetMp() - 50);
			iSkillDamage = GetAttackPoint() * GetInt() + 50;

		}
		else if (3 == iSelectSkill)
		{
			
			std::cout << "3. ���׿� ~ �ߵ� ! " << std::endl;
			SetMp(GetMp() - 100);
			iSkillDamage = GetAttackPoint() * GetInt() + 500;
		}
	}
	return iSkillDamage;
	
}

void Player::DrinkingPoseon()
{
	system("cls");
	if (0 == GameSystem::GetInstance()->GetPoseonInventory().size())
	{
		std::cout << "���濡 ������ �����ϴ�.. " << std::endl;
		return;
	}
	
	int iInvenPosenSize = GameSystem::GetInstance()->GetPoseonInventory().size();
	std::cout << "========================================================" << std::endl;

	InventoryPoseonView();
	std::cout << "========================================================" << std::endl;

	int i = 1;

	bool isSelect = false ;

	std::list<sData> lPosean = GameSystem::GetInstance()->GetPoseonInventory();
	std::list<sData>::iterator it;
	std::list<sData>::iterator itBegin = lPosean.begin();
	std::list<sData>::iterator itEnd = lPosean.end();

	while (false == isSelect)
	{
		std::cout << "������ ������ �ּ��� (0: ������ ) : ";
		std::cin >> iPlayerSelect;

		if (0 == iPlayerSelect)
		{
			isSelect = true;
			break;
		}
		else if (std::cin.fail() ||
			0 > iPlayerSelect || iInvenPosenSize < iPlayerSelect)
		{
			std::cout << "�߸��� ���� �Է��߽��ϴ�. �ٽ� �Է��� �ּ��� !" << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}


		for (it = itBegin; it != itEnd; it++, i++)
		{
			if (iPlayerSelect == i)
			{
				std::cout << "�������� ����߽��ϴ�. " << std::endl;
				if (GetMaxHp() > GetHp() + it->iHpInfo)
				{
					SetHp(GetMaxHp());
				}
				else
				{
					SetHp(GetHp() + it->iHpInfo);
				}
				if (GetMaxMp() > GetHp() + it->iHpInfo)
				{
					SetMp(GetMaxMp());
				}
				else
				{
					SetMp(GetMp() + it->iMpInfo);

				}
				SetLv(GetLv() + it->iLevelUpInfo);
				it = lPosean.erase(it);
				break;
			}
		}

		if (0 == GameSystem::GetInstance()->GetPoseonInventory().size())
		{
			std::cout << "���濡 ������ �����ϴ�.. " << std::endl;
			isSelect = true;
		}

	}
	

	


}

