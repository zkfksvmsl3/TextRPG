#include "Character.h"

#include <iostream>


Character::Character()
{
	iHp = 100;
	iMp = 100;
	iAttackPoint = 30;
	iDefensePoint = 10;
	iExp = 10;
}


Character::~Character()
{

}

void Character::Init(int _number, Character * _charater)
{
}
void Character::Init(int _number)
{
}

void Character::SetName(std::string _name)
{
}

void Character::AddInventory(std::list<Item>::iterator& it)
{
}

void Character::InventoryView()
{

}

void Character::PlayerState()
{
}

int Character::GetInventorySize()
{
	return 0;
}

int Character::DeleteInventoryItem(int iPlayerSelect)
{
	return 0;
}



void Character::CharacterWear(sEquipment* _eq, std::string sName, int _iSelect)
{
}

void Character::ChangeWear(sEquipment* _eq, std::string sName, int _iSelect)
{
}

void Character::ChangeWearState( int iAttackPointInfo, int iDefensiveInfo, int iStrInfo, int iDexInfo, int iIntInfo)
{
	
}

void Character::Update()
{
}

void Character::DecreaseHP(int _attackPoint)
{
}

void Character::Reset(int _hp)
{
}

void Character::IncreaseExp( Character * _monster)
{
}

int Character::Skill()
{
	return 0;
}

int Character::SkillDamge(int iSelectSkill)
{
	return 0;
}

void Character::DrinkingPoseon()
{
}
