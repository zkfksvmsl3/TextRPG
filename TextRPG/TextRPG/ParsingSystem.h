#pragma once

#include <string>
#include <vector>

#include "GameSystem.h"

class sParagraph;
class Item;
class Store;
class Character;

class ParsingSystem
{
public:
	ParsingSystem();
	~ParsingSystem();
public:
	sParagraph* CSVParsing(const char* fileName, int* paragraphCount);
	void ItemCSVParsing(const char* fileName, Item* _item, Store* _store);
	void ItemTableCSVParsing(const char* fileName, std::vector<sData>* _vector);
	void SetDataInit(sData* _data, int iItemCode, eItemType itemType, std::string sItemName, int iPrice, int iFristTemp, int iSecondTemp, int iThirdTemp, std::string sInfoText);
	void PlayerParsing(const char* fileName, Character* _player, bool* _isLoad);

};

