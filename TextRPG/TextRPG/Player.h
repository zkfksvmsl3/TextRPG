#pragma once

#include "Character.h"
#include "GameSystem.h"




class Player
	: public Character
{
private:
	int iPlayerSelect;
	char chText;
	std::string sPlayerName;
	eJobType jobType;
	int iLv;
	int iStr;
	int iDex;
	int iInt;
	int iGold;
	int iStatePoint;
	int iInvenSize;
	int iMaxHp;
	int iMaxMp;
	sEquipment* eq;
	std::list<sData> lPoseanList;
public:
	Player();
	~Player();
public:
	void SetName(std::string _name);
	void Init(int _number);
	void WarriorInit(eJobType type);
	void ArcherInit(eJobType type);
	void WizardInit(eJobType type);
public:
	int GetGold() { return iGold; }
	void SetGold(int _gold) { iGold = _gold; }
	std::list<std::pair< std::string, int>> GetInventory() { return vInventory; }
	void AddInventory(std::list<Item>::iterator& it);
	void InventoryView();
	void InventoryInfoView(int _iSelect, sEquipment* _eq);
	void InventoryPoseonView();
	int GetInventorySize();
	int DeleteInventoryItem(int iPlayerSelect);
	int DeleteInventoryItem(std::string _name);

public:
	void PlayerState();
	void CharacterInfo();
	void CharacterEquipment(sEquipment* _eq);
	void CharacterInventory(sEquipment* _eq);
	void StateUp();
	
public:
	eJobType GetjobType() { return jobType; }
	std::string GetName() { return sPlayerName;  }
	int GetHp() { return iHp; }
	int GetMp() { return iMp; }
	int GetAttackPoint() { return iAttackPoint; }
	int GetDefensePoint() { return iDefensePoint; }
	int GetLv() { return iLv; }
	int GetStr() { return iStr; }
	int GetDex() { return iDex; }
	int GetInt() { return iInt; }
	int GetStatePoint() { return iStatePoint; }
	int GetExp() { return iExp; }
	int GetMaxHp() { return iMaxHp; }
	int GetMaxMp() { return iMaxHp; }

	void SetLevel(int _lv) { iLv = _lv; }
	void SetJob(eJobType _job) { jobType = _job; }
	void SetLv(int _lv) { iLv = _lv; }
	void SetHp(int _hp) { iHp = _hp; }
	void SetMp(int _mp) { iMp = _mp; }
	void SetAttackPoint(int _point) { iAttackPoint = _point; }
	void SetDefensePoint(int _point) { iDefensePoint = _point; }
	void SetStr(int _str) { iStr = _str; }
	void SetDex(int _dex) { iDex = _dex; }
	void SetInt(int _int) { iInt =_int; }
	void SetStatePoint(int _point) { iStatePoint = _point; }
	void SetExp(int _exp) { iExp = _exp; }
	void SetMaxHp(int _hp) { iMaxHp = _hp; }
	void SetMaxMp(int _mp) { iMaxHp = _mp; }

public:
	void CharacterWear(sEquipment* _eq, std::string sName ,int _iSelect);
	void ChangeWear(sEquipment* _eq, std::string sName, int _iSelect);
	void ChangeWearState( int iAttackPointInfo, int iDefensiveInfo, int iStrInfo, int iDexInfo, int iIntInfo);
public:
	void Update();
	void WarriorStateUpdate();
	void ArcherStateUpdate();
	void WizardStateUpdate();
	void DecreaseHP(int _attackPoint);
	void Reset(int _hp);
	void IncreaseExp( Character* _monster);
	void LevelUp();
	int Skill();
	int SkillDamge(int iSelectSkill);
	void DrinkingPoseon();

};

