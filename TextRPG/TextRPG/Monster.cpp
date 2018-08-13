#include "Monster.h"



Monster::Monster()
{
	// 초기화 
	iMHp = 100;
	iMAttackPoint = 10;
	iMDefensePoint = 10;
	iMGold = 100;
	iMExp = 10;
}


Monster::~Monster()
{
}

void Monster::SetName(std::string _name)
{
	sMonsterName = _name;
}

void Monster::Init(int _number)
{
}


void Monster::Init(int _number, Character* _player)
{
	// 호출 시 몬스터 초기화 
	switch (_number)
	{
	case 1:
		sMonsterName = "고블린";
		SetName(sMonsterName);
		SetHp(_player->GetHp() + GetHp());
		SetAttackPoint(50);
		SetDefensePoint(20);
		SetExp(100);
		break;
	case 2:
		sMonsterName = "슬라임";
		SetName(sMonsterName);
		SetHp(_player->GetHp() + GetHp());
		SetAttackPoint(20);
		SetDefensePoint(20);
		SetExp(20);
		break;
	case 3:
		sMonsterName = "오크";
		SetName(sMonsterName);
		SetHp(_player->GetHp() + GetHp() *2);
		SetAttackPoint(150);
		SetDefensePoint(50);
		SetExp(150);

		break;
	case 4:
		sMonsterName = "궁수 고블린";
		SetName(sMonsterName);
		SetHp(_player->GetHp() + (GetHp()/2));
		SetAttackPoint(70);
		SetDefensePoint(30);
		SetExp(70);
		break;
	case 5:
		sMonsterName = "미노타우르스";
		SetName(sMonsterName);
		SetHp(_player->GetHp() + GetHp() + 1000);
		SetAttackPoint(300);
		SetDefensePoint(200);
		SetExp(300);
		break;
	case 6:
		sMonsterName = " 쥐";
		SetName(sMonsterName);
		SetHp(50);
		SetAttackPoint(5);
		SetDefensePoint(5);
		SetExp(5);

		break;
	case 7:
		sMonsterName = "좀비";
		SetName(sMonsterName);

		SetHp(50);
		SetAttackPoint(50);
		SetDefensePoint(0);
		SetExp(50);

		break;
	case 8:
		sMonsterName = "도적";
		SetName(sMonsterName);
		SetHp(_player->GetHp() + GetHp() * _player->GetLv());
		SetAttackPoint(20 + _player->GetStr() + _player->GetDex());
		SetDefensePoint(20 + _player->GetDex());
		SetExp(100);

		break;
	case 9:
		sMonsterName = "마왕";
		SetHp(_player->GetHp() + (GetHp() + 1000 * _player->GetLv()));
		SetAttackPoint(500 + _player->GetStr() + _player->GetDex());
		SetDefensePoint(500 + _player->GetDex());
		SetExp(5000);

		break;
	default:
		break;
	}
}

int Monster::GetGold()
{
	return 0;
}

void Monster::SetGold(int _gold)
{
}

void Monster::Update()
{
}

void Monster::DecreaseHP(int _attackPoint)
{
	// Battle 
	SetHp(GetHp() - _attackPoint);
	if (GetHp() <= 0)
	{
		SetHp(0);
	}
}
