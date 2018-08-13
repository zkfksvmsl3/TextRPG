#include "Player.h"

#include <iostream>


Player::Player()
{
	// 초기화 
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
	// 직업 초기화 
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
	 // 인벤토리 추가 ( 30 까지 제한)  
	if (iInvenSize > 30)
	{
		std::cout << " 가방의 크기를 초과 했습니다! " << std::endl;
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
	std::cout << "======번호==아이템명====가격=======" << std::endl;
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
			std::cout << "[ 번호 : " << i << " ]" << "   " <<
				" [  아이템명 : " << it->sNameInfo << " ] " << "   " <<
				" [  HP 회복 : " << it->iHpInfo << " ] " << "   " <<
				" [  MP 회복 : " << it->iMpInfo << " ] " << "   " <<
				" [  레벨업  : " << it->iLevelUpInfo << " ] " << std::endl;
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
		std::cout << " 아무것도 없습니다! " << std::endl;
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
		std::cout << " 아무것도 없습니다! " << std::endl;
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
	
	// 캐릭터 정보
	
	bool isQuit = false;
	while (false == isQuit)
	{
		std::cout << "1. 캐릭터 정보 / 2. 캐릭터 장비 / 3. 캐릭터 가방 / 4. 돌아가기" << std::endl;
		std::cout << "숫자를 입력해 주세요 : ";
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
			std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
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
		std::cout << "       JOB : " << " 전 사 " << std::endl;
		break;
	case eJobType::ARCHER:
		std::cout << "       JOB : " << " 궁 수 " << std::endl;
		break;
	case eJobType::WIZARD:
		std::cout << "       JOB : " << " 마 법 사 " << std::endl;
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

			std::cout << "스텟포인트가 " << GetStatePoint() << " 있습니다.. 스텟을 찍겠습니까?? ( y / n )" << std::endl;
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
				std::cout << "포인트가 없습니다!" << std::endl;
				break;
			}
		}
	}

	system("cls");

}

void Player::CharacterEquipment(sEquipment* _eq)
{
	// 장비창
	system("cls");
	std::cout << "----방어구----" << std::endl;
	std::cout << " 머    리 : " << " [ "<<_eq->sHeadGear << " ] " << std::endl;
	std::cout << " 상    의 : " << " [ " << _eq->sChestGear << " ] " << std::endl;
	std::cout << " 하    의 : " << " [ " << _eq->sPantsGear << " ] " << std::endl;
	std::cout << " 신   발  : " << " [ " <<_eq->sShoesGear << " ] " << std::endl;
	std::cout << "----무  기----" << std::endl;
	std::cout << " 오 른 손 : " << " [ " << _eq->sRighthandGear << " ] " << std::endl;
	std::cout << " 왼    손 : " << " [ " << _eq->sLeftHandGear << " ] " << std::endl;
	system("pause");
	system("cls");
}

void Player::CharacterInventory(sEquipment* _eq)
{
	// 인벤토리 창 
	system("cls");

	if (0 == GetInventorySize())
	{
		std::cout << "아무 것도 없습니다.." << std::endl;
		system("pause");
		system("cls");
		return;
	}
	

	while (1)
	{
		std::cout << "=======================================" << std::endl;
		std::cout << "1. 소모품 , 2. 무기 , 3. 장비 : , 4. 나가기 " << std::endl;
		std::cout << "=======================================" << std::endl;

		std::cout << "어느 가방으로 이동 하시겠습니까?";
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
			std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}
		else
		{
			std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
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
		std::cout <<"현재 스텟포인트 ! : "<< GetStatePoint()<< std::endl;
		std::cout << "1. 힘 / 2. 민첩 / 3. 지능 " << std::endl;
		std::cout << "어느곳에 포인트를 올리겠습니까? :" ;
		std::cin >> iPlayerSelect;

		
		if(1 == iPlayerSelect)
		{
			std::cout << "몇 포인트를 올리겠습니까? :";
			std::cin >> iPointUp;

			if (GetStatePoint() < iPointUp || std::cin.fail())
			{
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
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
			std::cout << "몇 포인트를 올리겠습니까? :";
			std::cin >> iPointUp;

			
			if (GetStatePoint() < iPointUp || std::cin.fail())
			{
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
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
			std::cout << "몇 포인트를 올리겠습니까? :";
			std::cin >> iPointUp;

			if (GetStatePoint() < iPointUp || std::cin.fail())
			{
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
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
			std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}
		// 스텟 초기화 
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
			std::cout << "1. 오른손 / 2. 왼손 " << std::endl;
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
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			else
			{
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
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
			std::cout << "1. 오른손 / 2. 왼손 " << std::endl;
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
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
			else
			{
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 " << std::endl;
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
		std::cout << "1. 스매쉬! ( 힘 x 공격력 , 마나 10 ) " << std::endl;
		std::cout << "2. 필살 스매쉬 ! ( 힘 x 공격력 + 50 , 마나 50 )  " << std::endl;
		std::cout << "3. 궁극 스매쉬 ! ( 힘 x 공격력 + 500  , 마나 100)  " << std::endl;
		std::cout << "4. 나가기 " << std::endl;
		std::cout << "현재 MP : " << GetMp() << std::endl;
		while (1)
		{
			std::cout << "어떤 스킬을 사용하시겠습니까? ( 1 ~4 ) :";
			std::cin >> iPlayerSelect;

			if (1 == iPlayerSelect)
			{
				if (10 > GetMp())
				{
					std::cout << "마나가 부족 합니다.."<< std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (2 == iPlayerSelect)
			{
				if (50 > GetMp())
				{
					std::cout << "마나가 부족 합니다.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (3 == iPlayerSelect)
			{
				if (100 > GetMp())
				{
					std::cout << "마나가 부족 합니다.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (4 == iPlayerSelect)
			{
				std::cout << "선택창으로 이동 합니다." << std::endl;
				break;
			}
			else
			{
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요! " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}
	}
	else if (GetjobType() == eJobType::ARCHER)
	{
		std::cout << "1. 파워샷! ( 민 x 공격력 , 마나 10 ) " << std::endl;
		std::cout << "2 .필살 파워샷 ! ( 민 x 공격력 + 50 , 마나 50 )  " << std::endl;
		std::cout << "3. 궁극 파워샷 ! ( 민 x 공격력 + 500  , 마나 100)  " << std::endl;
		std::cout << "4. 나가기 " << std::endl;
		std::cout << "현재 MP : " << GetMp() << std::endl;
		while (1)
		{
			std::cout << "어떤 스킬을 사용하시겠습니까? ( 1 ~4 ) :";
			std::cin >> iPlayerSelect;

			if (1 == iPlayerSelect)
			{
				if (10 > GetMp())
				{
					std::cout << "마나가 부족 합니다.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (2 == iPlayerSelect)
			{
				if (50 > GetMp())
				{
					std::cout << "마나가 부족 합니다.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (3 == iPlayerSelect)
			{
				if (100 > GetMp())
				{
					std::cout << "마나가 부족 합니다.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (4 == iPlayerSelect)
			{
				std::cout << "선택창으로 이동 합니다." << std::endl;
				break;
			}
			else
			{
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요! " << std::endl;
				GameSystem::GetInstance()->StdCinClear();

				continue;
			}
		}
	}
	else if (GetjobType() == eJobType::WIZARD)
	{

		std::cout << "1. 파이어볼! ( 지 x 공격력 , 마나 10 ) " << std::endl;
		std::cout << "2 . 아이스볼! ( 지 x 공격력 + 50 , 마나 50 )  " << std::endl;
		std::cout << "3. 메테오 ! ( 지 x 공격력 + 500 , 마나 100)  " << std::endl;
		std::cout << "4. 나가기 " << std::endl;
		std::cout << "현재 MP : " << GetMp() << std::endl;
		while (1)
		{
			std::cout << "어떤 스킬을 사용하시겠습니까? ( 1 ~4 ) :";
			std::cin >> iPlayerSelect;

			if (1 == iPlayerSelect)
			{
				if (10 > GetMp())
				{
					std::cout << "마나가 부족 합니다.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;
			}
			else if (2 == iPlayerSelect)
			{
				if (50 > GetMp())
				{
					std::cout << "마나가 부족 합니다.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (3 == iPlayerSelect)
			{
				if (100 > GetMp())
				{
					std::cout << "마나가 부족 합니다.." << std::endl;
					GameSystem::GetInstance()->StdCinClear();

					continue;
				}
				break;

			}
			else if (4 == iPlayerSelect)
			{
				std::cout << "선택창으로 이동 합니다." << std::endl;
				break;
			}
			else
			{
				std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요! " << std::endl;
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
			std::cout << "1. 스매쉬! ~ 발동!" << std::endl;

			SetMp(GetMp() - 10);
			iSkillDamage = GetAttackPoint() * GetStr();
		}
		else if (2 == iSelectSkill)
		{
			std::cout << "2. 필살 스매쉬 ! ~ 발동!  " << std::endl;
			SetMp(GetMp() - 50);
			iSkillDamage = GetAttackPoint() * GetStr() + 50;

		}
		else if (3 == iSelectSkill)
		{
			std::cout << "3. 궁극 스매쉬 !  ~ 발동! " << std::endl;
			SetMp(GetMp() - 100);
			iSkillDamage = GetAttackPoint() * GetStr() + 500;
		}
	}
	else if (GetjobType() == eJobType::ARCHER)
	{
		if (1 == iSelectSkill)
		{
			std::cout << "1. 파워샷! ~ 발동 !" << std::endl;
			SetMp(GetMp() - 10);
			iSkillDamage = GetAttackPoint() * GetDex();
		}
		else if (2 == iSelectSkill)
		{
			std::cout << "2 .필살 파워샷 !  ~ 발동 !  " << std::endl;
			SetMp(GetMp() - 50);
			iSkillDamage = GetAttackPoint() * GetDex() + 50;

		}
		else if (3 == iSelectSkill)
		{

			std::cout << "3. 궁극 파워샷 !  ~ 발동 !  " << std::endl;
			SetMp(GetMp() - 100);
			iSkillDamage = GetAttackPoint() * GetDex() + 500;
		}
	}
	else if (GetjobType() == eJobType::WIZARD)
	{
		if (1 == iSelectSkill)
		{
			std::cout << "1. 파이어볼 ~ 발동 ! " << std::endl;
			SetMp(GetMp() - 10);
			iSkillDamage = GetAttackPoint() * GetInt();
		}
		else if (2 == iSelectSkill)
		{
			std::cout << "2 . 아이스볼 ~ 발동 ! " << std::endl;
			SetMp(GetMp() - 50);
			iSkillDamage = GetAttackPoint() * GetInt() + 50;

		}
		else if (3 == iSelectSkill)
		{
			
			std::cout << "3. 메테오 ~ 발동 ! " << std::endl;
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
		std::cout << "가방에 포션이 없습니다.. " << std::endl;
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
		std::cout << "포션을 선택해 주세요 (0: 나가기 ) : ";
		std::cin >> iPlayerSelect;

		if (0 == iPlayerSelect)
		{
			isSelect = true;
			break;
		}
		else if (std::cin.fail() ||
			0 > iPlayerSelect || iInvenPosenSize < iPlayerSelect)
		{
			std::cout << "잘못된 값을 입력했습니다. 다시 입력해 주세요 !" << std::endl;
			GameSystem::GetInstance()->StdCinClear();

			continue;
		}


		for (it = itBegin; it != itEnd; it++, i++)
		{
			if (iPlayerSelect == i)
			{
				std::cout << "아이템을 사용했습니다. " << std::endl;
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
			std::cout << "가방에 포션이 없습니다.. " << std::endl;
			isSelect = true;
		}

	}
	

	


}

