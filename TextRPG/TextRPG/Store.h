#pragma once

#include <map>
#include <list>
#include <iomanip>
#include <iostream>
#include <conio.h>

#include "ParsingSystem.h"
#include "GameSystem.h"

class Character;

enum eStoreType
{
	POTION,
	AMS,
	DEFENSIVE,
	DEFAULT,
};

class Store
{
protected:
	int iPlayerSelect;
	char chText;

	ParsingSystem* parser;
	Item* _item;
	eStoreType m_StoreType;
protected:

public:
	Store();
	~Store();

public:
	virtual void ItemInit();
	virtual void EnterStore(Character* _character);
	virtual void LeaveStore();
	virtual void ItemInput(Item* item);
public:
	eStoreType GetStoreType() { return m_StoreType; }


};

