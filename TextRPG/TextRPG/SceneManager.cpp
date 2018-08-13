#include "SceneManager.h"

#include "TitleScene.h"
#include "PlayerGenerationScene.h"
#include "BeginningVillageScene.h"
#include "DungeonScene.h"


SceneManager* SceneManager::_instance = 0;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

SceneManager* SceneManager::GetInstance()
{
	if (0 == _instance)
	{
		_instance = new SceneManager();
	}
	return _instance;
}

void SceneManager::ChangeScene(eScene sceneType, int _index)
{
	switch (sceneType)
	{
	case eScene::SCENE_TITLE:
		_scene = new TitleScene();
		_scene->Init(_index);
		break;
	case eScene::SCENE_CREATECHACTER:
		_scene = new PlayerGenerationScene();
		_scene->Init(_index);
		break;
	case eScene::SCENE_VILLAGE:
		_scene = new BeginningVillageScene();
		_scene->Init(_index);
		break;
	case eScene::SCENE_DUNGEON:
		_scene = new DungeonScene();
		_scene->Init(_index);
		break;
	}
}

void SceneManager::Update()
{
	_scene->Update();
}

void SceneManager::Release()
{
	delete _scene;
	delete _instance;
}
