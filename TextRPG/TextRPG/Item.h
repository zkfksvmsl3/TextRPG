#pragma once

#include <string>


enum eItemType
{
	HPPOTION,
	MPPOTION,
	WEAPON,
	SHIELD,
	DEFENSIVE_HEAD,
	DEFENSIVE_CHEST,
	DEFENSIVE_TROUSERS,
	DEFENSIVE_SHOES,
	APPLE = 77,
};

class Store;

class Item
{
private:
	Store * _store;
public:
	int iItemCode;
	eItemType eType;
	std::string sItemName;
	int iPrice;
	
public:
	Item();
	~Item();
public:
	void SetItemMap(int _index, int _iTemCode, eItemType _type, std::string _name, int _price);
	void Release();
	
};