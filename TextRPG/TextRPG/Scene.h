#pragma once
#include "SceneManager.h"

class Scene
{
protected:
	eScene sceneType;
	
	int iPlayerSelect;
	char chText;

public:
	Scene();
	~Scene();
public:
	virtual void Init(int _index) = 0;
	virtual void Update() = 0;
public:
	void SetSceneType(eScene _type);
	eScene GetSceneType();
};

