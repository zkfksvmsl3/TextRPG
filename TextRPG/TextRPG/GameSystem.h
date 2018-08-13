#pragma once
#include <string>
#include <vector>
#include <list>

#include "Item.h"
#include "Character.h"

class ParsingSystem;
enum eCharacterType
{
	PLAYER,
};

struct sData
{
	
	int iCodeInfo = 0;
	eItemType eTypeInfo;
	std::string sNameInfo;
	int iPriceInfo = 0;
	int iHpInfo = 0;
	int iMpInfo = 0;
	int iLvInfo = 0;
	int iLevelUpInfo = 0;
	int iAttackPointInfo = 0;
	int iDefensiveInfo = 0;
	int iStrInfo = 0;
	int iDexInfo = 0;
	int iIntInfo = 0;
	std::string sTextInfo;
};

class GameSystem
{
private:
	Character* _character;
	ParsingSystem* _parser;
	bool isGameProgress;
	int iPlayerSelect;
	char chText;
	private:
	std::vector<sData> vRecveryInfo;
	std::vector<sData> vArmsInfo;
	std::vector<sData> vDefensiveInfo;
	std::list<sData> lPoseonInventory;
public:
	std::vector<sData> GetRecveryInfo() { return vRecveryInfo; }
	std::vector<sData> GetArmsInfo() { return vArmsInfo; }
	std::vector<sData> GetDefensiveInfo() { return vDefensiveInfo; }
	std::list<sData> GetPoseonInventory() { return lPoseonInventory; }
private:
	GameSystem();
	~GameSystem();
private:
	static GameSystem* _instance;
public:
	static GameSystem* GetInstance();
public:
	void InitPosen(Character* _player);
	void CharacterCreate(eCharacterType type);
	Character* GetCharacter() { return _character; }
	void PlayerInit(int _number);
	void SetPlayerName(std::string _name);
	void InitItemInfo();
	void FindinventoryInfoView(std::list<std::pair< std::string, int>>* vInventory, int _iSelect, sEquipment* _eq);
public:
	void CollisionEvent(Character* _player, Character* _monster, int _rand, int* nextBranch, bool* isQuit);
	void Battle(Character* _player, Character* _monster, int* nextBranch, bool* isQuit);
public:
	void Save(Character* _player);
	void Load(bool* _isLoad);
	void SetIsGameProgress(bool _isGameProgress) { isGameProgress = _isGameProgress; }
	bool GetIsGameProgress() { return isGameProgress; }
public:
	void StdCinClear();
	void Release();
};

