#pragma once
#include "Store.h"


class GeneralStore
	: public Store
{
public:
	GeneralStore();
	~GeneralStore();
public:
	std::list<Item> recoveryItemList;
	std::list<Item>::iterator it;
public:
	void ItemInit();
	void ItemInput(Item* item);
	void EnterStore(Character* _character);
	void PurchaseStore(Character* _character, bool* _isQuit, int iItemIndex);
	void ItemPrint(int* iItemIndex);
	void ItemSale(Character* _character, bool* _isQuit);
	void SelectSaleItem(Character* _character);

};

