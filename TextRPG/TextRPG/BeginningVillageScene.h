#pragma once
#include "Scene.h"


class sParagraph;
class ParsingSystem;
class Item;
class Character;

class BeginningVillageScene
	:public Scene
{
private:
	int iRand;
	int pargraphCount;
	int iBranch;

	bool isQuit;
	sParagraph* paragraphList;
	ParsingSystem* parser;
	Item* itemList;
	Character* _character;
public:
	BeginningVillageScene();
	~BeginningVillageScene();
public:
	void Init(int _index);
	void Update();
public:
	void InitMap();
	void InitVillage(int iRandom);
	void VillageUpdate(int iRandom);
	void InitStore();


	
};