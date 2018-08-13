#pragma once
#include "Scene.h"
#include "SceneManager.h"

class sParagraph;
class ParsingSystem;
class PlayerGenerationScene
	: public Scene
{
private:
	sParagraph* paragraphList;
	ParsingSystem* parser;
	int pargraphCount;
	int iBranch;
	bool isQuit;
public:
	PlayerGenerationScene();
	~PlayerGenerationScene();
public:
	void Init(int _index);
	void Update();

};

