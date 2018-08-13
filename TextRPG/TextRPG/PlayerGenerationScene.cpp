#include "PlayerGenerationScene.h"

#include <iostream>
#include <Windows.h>

#include "sParagraph.h"
#include "ParsingSystem.h"
#include "Character.h"
#include "SceneManager.h"



PlayerGenerationScene::PlayerGenerationScene()
{
	iPlayerSelect = 0;
	parser = new ParsingSystem();
	iBranch = 0;
	isQuit = false;
}

PlayerGenerationScene::~PlayerGenerationScene()
{
	delete parser;
}

void PlayerGenerationScene::Init(int _index)
{
	pargraphCount = 0;
	paragraphList = parser->CSVParsing("PlayerGenerationScene.csv", &pargraphCount);
	SetSceneType(eScene::SCENE_CREATECHACTER);
}

void PlayerGenerationScene::Update()
{
	while (false == isQuit)
	{
		if (iBranch < pargraphCount)
		{
			paragraphList[iBranch].Process(&iBranch,sceneType ,&isQuit);
		}
	}
}
