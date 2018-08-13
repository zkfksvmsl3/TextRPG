#include "ParsingSystem.h"

#include <fstream>	
#include <queue>
#include <string>
#include <iostream>
#include <conio.h>

#include "sParagraph.h"
#include "sString.h"
#include "StringText.h"
#include "StringName.h"
#include "StringBranch.h"
#include "StringNext.h"
#include "StringQuit.h"
#include "StringRandom.h"
#include "Item.h"
#include "Store.h"


ParsingSystem::ParsingSystem()
{
}


ParsingSystem::~ParsingSystem()
{
}

sParagraph* ParsingSystem::CSVParsing(const char* fileName, int* paragraphCount)
{
	std::ifstream inFile(fileName);
	
	std::queue<std::string> q_data;
	std::string sBuffer;
	std::string sRecord;
	std::string textString;
	int iIndex = 0;
	int iLineNo = 0;
	eStringType iTextType;
	//int iCount = 0;
	int iParagraph = 0;

	if (!inFile.is_open())
	{
		std::cout << "File is Not Read" << std::endl;
	}

	// File Read
	getline(inFile, sBuffer);

	int paragraphIndex = 0;			// 현재 문단번호
	int prevParagraphIdx = -1;		// 이전 문단번호

	while (getline(inFile, sBuffer))
	{
		q_data.push(sBuffer);
		//std::cout << sBuffer << std::endl;

		iIndex = sBuffer.find(",");
		textString = sBuffer.substr(0, iIndex);
		paragraphIndex = stoi(textString);

		if (paragraphIndex != prevParagraphIdx)
		{
			prevParagraphIdx = paragraphIndex;
			(*paragraphCount)++;

		}

	}
	
	// 
	inFile.close();


	sParagraph* paragraphList = new sParagraph[(*paragraphCount)];

	// 초기화 ( 처음으로 ) 
	paragraphIndex = 0;
	prevParagraphIdx = -1;
	
	while (!q_data.empty())
	{
		sRecord = q_data.front().substr(0, q_data.front().size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		paragraphIndex = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());
		
		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iLineNo = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());
		
		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iTextType = (eStringType)stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		if (paragraphIndex != prevParagraphIdx)
		{
			prevParagraphIdx = paragraphIndex;
			paragraphList[paragraphIndex]._currentNode = 0;		//초기화
																	//(*paragraphCount)++;
		}

		//
		sString* newString = 0;

		switch (iTextType)
		{
		case eStringType::TEXT:
			newString = new StringText();
			break;
		case eStringType::NAME:
			newString = new StringName();
			break;
		case eStringType::BRANCH:
			newString = new StringBranch();
			break;
		case eStringType::NEXT:
			newString = new StringNext();
			break;
		case eStringType::QUIT:
			newString = new StringQuit();
			break;
		case eStringType::RANDOM:
			newString = new StringRandom();
		}
		//
		newString->Init(iLineNo, iTextType, textString);
		paragraphList[paragraphIndex].AddStringToParagraph(newString);



		q_data.pop();


	}

	return paragraphList;
}

void ParsingSystem::ItemCSVParsing(const char * fileName, Item* _item, Store* _store)
{
	std::ifstream inFile(fileName);

	std::queue<std::string> q_data;
	std::string sBuffer;
	std::string sRecord;
	std::string textString;
	std::string sItemName;
	int iIndex = 0;
	int iTextNum = 0;
	int iItemCode = 0;
	eItemType itemType;
	int iItemPrice = 0;

	//int iCount = 0;

	if (!inFile.is_open())
	{
		std::cout << "File is Not Read" << std::endl;
	}

	// File Read
	while (getline(inFile, sBuffer))
	{
		q_data.push(sBuffer);
		//std::cout << sBuffer << std::endl;
	}
	//
	inFile.close();

	q_data.pop();

	while (!q_data.empty())
	{
		sRecord = q_data.front().substr(0, q_data.front().size());
		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iTextNum = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iItemCode = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		itemType = (eItemType)stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		sItemName = textString;
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iItemPrice = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		_item->SetItemMap(iTextNum, iItemCode, itemType, sItemName, iItemPrice);
		
		if (_store->GetStoreType() == eStoreType::AMS)
		{
			if (itemType == eItemType::WEAPON ||
				itemType == eItemType::SHIELD)
			{
				_store->ItemInput(_item);
			}
		}
		else if (_store->GetStoreType() == eStoreType::DEFENSIVE)
		{
			if (itemType == eItemType::DEFENSIVE_CHEST ||
				itemType == eItemType::DEFENSIVE_HEAD ||
				itemType == eItemType::DEFENSIVE_SHOES ||
				itemType == eItemType::DEFENSIVE_TROUSERS)
			{
				_store->ItemInput(_item);
			}
		}
		else if (_store->GetStoreType() == eStoreType::POTION)
		{
			if (itemType == eItemType::HPPOTION ||
				itemType == eItemType::MPPOTION ||
				itemType == eItemType::APPLE)
			{
				_store->ItemInput(_item);
			}
		}

		q_data.pop();
	}


}

void ParsingSystem::ItemTableCSVParsing(const char * fileName, std::vector<sData>* _vector)
{
	std::ifstream inFile(fileName);

	std::queue<std::string> q_data;
	std::string sBuffer;
	std::string sRecord;
	std::string textString;
	std::string sItemName;
	std::string sInfoText;

	int iIndex = 0;
	int iTextNum = 0;
	int iItemCode = 0;
	int iPrice = 0;
	int iFristTemp = 0;
	int iSecondTemp = 0;
	int iThirdTemp = 0;

	eItemType itemType;
	

	//int iCount = 0;

	if (!inFile.is_open())
	{
		std::cout << "File is Not Read" << std::endl;
	}

	// File Read
	while (getline(inFile, sBuffer))
	{
		q_data.push(sBuffer);
		//std::cout << sBuffer << std::endl;
	}
	//
	inFile.close();

	q_data.pop();

	while (!q_data.empty())
	{
		sRecord = q_data.front().substr(0, q_data.front().size());
		
		// Code
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iItemCode = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//2 ItemType
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		itemType = (eItemType)stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//3 ItemName
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		sItemName = textString;
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//4 ItemPrice
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iPrice = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//5 FristTemp
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iFristTemp = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//6 SecondTemp
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iSecondTemp = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//7 ThirdTemp
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iThirdTemp = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//8 sInfoText
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		sInfoText = textString;
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		
		//Type

		sData _data;

		SetDataInit(&_data, iItemCode, itemType, sItemName, iPrice, iFristTemp, iSecondTemp, iThirdTemp,sInfoText);
		
		_vector->push_back(_data);

		q_data.pop();
	}

}

void ParsingSystem::SetDataInit(sData* _data,int iItemCode,eItemType itemType,std::string sItemName,int iPrice,int iFristTemp,int iSecondTemp,int iThirdTemp,std::string sInfoText)
{
	_data->iCodeInfo = iItemCode;
	_data->eTypeInfo = itemType;
	_data->sNameInfo = sItemName;
	_data->iPriceInfo = iPrice;
	_data->sTextInfo = sInfoText;

	switch (itemType)
	{
	case eItemType::HPPOTION:
		_data->iHpInfo = iFristTemp;
		_data->iMpInfo = iSecondTemp;
		_data->iLevelUpInfo = iThirdTemp;
		break;
	case eItemType::MPPOTION:
		_data->iHpInfo = iFristTemp;
		_data->iMpInfo = iSecondTemp;
		_data->iLevelUpInfo = iThirdTemp;
		break;
	case eItemType::APPLE:
		_data->iHpInfo = iFristTemp;
		_data->iMpInfo = iSecondTemp;
		_data->iLevelUpInfo = iThirdTemp;
		break;
	case eItemType::WEAPON:
		_data->iAttackPointInfo = iFristTemp;
		_data->iDefensiveInfo = iSecondTemp;
		_data->iLvInfo = iThirdTemp;
		break;
	case eItemType::SHIELD:
		_data->iAttackPointInfo = iFristTemp;
		_data->iDefensiveInfo = iSecondTemp;
		_data->iLvInfo = iThirdTemp;
		break;
	case eItemType::DEFENSIVE_CHEST:
		_data->iStrInfo = iFristTemp;
		_data->iDexInfo = iSecondTemp;
		_data->iIntInfo = iThirdTemp;
		break;
	case eItemType::DEFENSIVE_HEAD:
		_data->iStrInfo = iFristTemp;
		_data->iDexInfo = iSecondTemp;
		_data->iIntInfo = iThirdTemp;
		break;
	case eItemType::DEFENSIVE_SHOES:
		_data->iStrInfo = iFristTemp;
		_data->iDexInfo = iSecondTemp;
		_data->iIntInfo = iThirdTemp;
		break;
	case eItemType::DEFENSIVE_TROUSERS:
		_data->iStrInfo = iFristTemp;
		_data->iDexInfo = iSecondTemp;
		_data->iIntInfo = iThirdTemp;
		break;
	}
}

void ParsingSystem::PlayerParsing(const char * fileName, Character * _player, bool* _isLoad)
{
	std::ifstream inFile(fileName);

	std::queue<std::string> q_data;
	std::string sBuffer;
	std::string sRecord;
	std::string textString;
	int iIndex = 0;
	std::string sName;
	eJobType eJob;
	int iLv = 0;
	int iHp = 0;
	int iMp = 0;
	int iAttackPoint = 0;
	int iDefPoint = 0;
	int iStr = 0;
	int iDex = 0;
	int iInt = 0;
	int iGold = 0;

	if (!inFile.is_open())
	{
		std::cout << "File is Not Read" << std::endl;
		return;
	}

	while (getline(inFile, sBuffer))
	{
		q_data.push(sBuffer);
	}
	*_isLoad = true;
	q_data.pop();

	while (!q_data.empty())
	{
		sRecord = q_data.front().substr(0, q_data.front().size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		sName = textString;
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		eJob = (eJobType)stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iLv = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());


		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iHp = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());


		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iMp = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());


		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iAttackPoint = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iDefPoint = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());
		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iStr = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());
		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iDex = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());
		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iInt = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());

		//
		iIndex = sRecord.find(",");
		textString = sRecord.substr(0, iIndex);
		iGold = stoi(textString);
		sRecord = sRecord.substr(iIndex + 1, sRecord.size());
		
		//
		_player->SetName(sName);
		_player->SetJob(eJob);
		_player->SetLevel(iLv);
		_player->SetHp(iHp);
		_player->SetMp(iMp);
		_player->SetAttackPoint(iAttackPoint);
		_player->SetDefensePoint(iDefPoint);
		_player->SetStr(iStr);
		_player->SetDex(iDex);
		_player->SetInt(iInt);
		_player->SetGold(iGold);

		q_data.pop();
	}


}
