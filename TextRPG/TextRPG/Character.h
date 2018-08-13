#pragma once
#include <list>
#include <string>

#include "Item.h"

// 직업
enum eJobType
{
	NONE,
	WARRIOR = 2,
	ARCHER,
	WIZARD,
};

struct sEquipment
{
	// 방어구
	std::string sHeadGear;
	std::string sChestGear;
	std::string sPantsGear;
	std::string sShoesGear;

	// 착용 여부 
	bool IsHeadGear = false;
	bool IsChestGear = false;
	bool IsPantsGear = false;
	bool IsShoesGear = false;

	// 오른손 왼손
	std::string sRighthandGear;
	std::string sLeftHandGear;

	// 착용 여부
	bool IsRighthandGear = false;
	bool IsLeftHandGear = false;
};


class Character
{
protected:
	int iHp;
	int iMp;
	int iAttackPoint;
	int iDefensePoint;
	int iGold;
	int iExp;
	bool isLive;
	eJobType ejob;
protected:
	// 인벤토리 
	std::list<std::pair< std::string, int>> vInventory;
public:
	Character();
	~Character();
public:
	virtual std::list<std::pair< std::string, int>> GetInventory() { return vInventory; }
public:
	virtual void Init(int _number, Character* _charater);
	virtual void Init(int _number);
	virtual void SetName(std::string _name);
	virtual void AddInventory(std::list<Item>::iterator& it);
	virtual void InventoryView();
	virtual void PlayerState();
	virtual int GetInventorySize();
	virtual int DeleteInventoryItem(int iPlayerSelect);
public:
	virtual void SetGold(int _gold) = 0;

	virtual int GetGold() = 0;

public:
public:
	virtual std::string GetName() { return NULL; }

	virtual int GetHp() { return iHp; }
	virtual int GetMp() { return iMp; }
	virtual int GetAttackPoint() { return iAttackPoint; }
	virtual int GetDefensePoint() { return iDefensePoint; }
	virtual eJobType GetjobType() { return (eJobType)ejob; }
	virtual int GetLv() { return 0; }
	virtual int GetStr() { return 0; }
	virtual int GetDex() { return 0; }
	virtual int GetInt() { return 0; }
	virtual int GetStatePoint() { return 0; }
	virtual int GetExp() { return iExp; }
	virtual int GetMaxHp() { return iHp; }
	virtual int GetMaxMp() { return iMp; }

	virtual void SetLevel(int _lv) { }
	virtual void SetJob(eJobType _job) {}
	virtual void SetLv(int _lv) {  }
	virtual void SetHp(int _hp) {  }
	virtual void SetMp(int _mp) {  }
	virtual void  SetAttackPoint(int _point) { iAttackPoint=_point; }
	virtual void  SetDefensePoint(int _point) { iDefensePoint= _point; }
	virtual void SetStr(int _str) {  }
	virtual void SetDex(int _dex) {  }
	virtual void SetInt(int _int) {  }
	virtual void SetStatePoint(int _point) { }
	virtual void SetExp(int _exp) {  }

public:
	virtual void CharacterWear(sEquipment* _eq, std::string sName, int _iSelect);
	virtual void ChangeWear(sEquipment* _eq, std::string sName,int _iSelect);
	virtual void ChangeWearState(int iAttackPointInfo, int iDefensiveInfo, int iStrInfo, int iDexInfo, int iIntInfo);
	virtual void Update() = 0;
public:
	virtual void DecreaseHP(int _attackPoint);
	virtual bool IsLive() { return isLive; }
	virtual void Reset(int _hp);
	virtual void IncreaseExp(Character* _monster);
	virtual int Skill();
	virtual int SkillDamge(int iSelectSkill);
	virtual void DrinkingPoseon();


};

