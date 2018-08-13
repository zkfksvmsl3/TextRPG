#pragma once

class Scene;
enum eScene
{
	SCENE_TITLE,
	SCENE_CREATECHACTER,
	SCENE_VILLAGE,
	SCENE_DUNGEON,
};
class SceneManager
{
private:
	Scene* _scene;
private:
	SceneManager();
	~SceneManager();
private:
	static SceneManager* _instance;
public:
	static SceneManager* GetInstance();
public:
	void ChangeScene(eScene sceneType, int _index);
	void Update();
	void Release();
};
