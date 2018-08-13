#pragma once

#include "Character.h"

class Monster
	: public Character
{
private:
	int iMHp;
	int iMAttackPoint ;
	int iMDefensePoint;
	int iMGold;
	int iMExp ;
	std::string sMonsterName;
public:
	Monster();
	~Monster();
public:
	void SetName(std::string _name);
	std::string GetName() { return sMonsterName; }
	void Init(int _number);
	void Init(int _number, Character* _player);
	int GetGold();
	void SetGold(int _gold);
	void Update();
public:
	int GetHp() { return iMHp; }
	void SetHp(int _hp) { iMHp = _hp; }

	int GetAttackPoint() { return iMAttackPoint; }
	void SetAttackPoint(int _point) { iMAttackPoint = _point; }

	int GetDefensePoint() { return iMDefensePoint; }
	void SetDefensePoint(int _point) { iMDefensePoint = _point; }

	int GetExp() { return iMExp; }
	void SetExp(int _exp) { iMExp = _exp; }
public:
	void DecreaseHP(int _attackPoint);

};

