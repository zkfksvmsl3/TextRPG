#pragma once

#include "sString.h"

class Character;
class StringRandom
	:public sString
{
private:
	Character* _monster;
	Character* _player;

public:
	StringRandom();
	~StringRandom();
public:
	void Process(int* nextBranch, eScene type, bool* isQuit);
	void MonsterEvent(int iRand, Character* _player, int* nextBranch, bool* isQuit);
};

