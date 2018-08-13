#include "Item.h"

#include <iostream>

#include "Store.h"


Item::Item()
{
	_store = new Store();
}


Item::~Item()
{
	delete _store;
}

void Item::SetItemMap(int _index, int _iTemCode, eItemType _type, std::string _name, int _price)
{
	iItemCode = _iTemCode;
	eType = _type;
	sItemName = _name;
	iPrice = _price;

	
}

void Item::Release()
{
	delete _store;
}


