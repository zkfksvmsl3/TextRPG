#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{

}

void Scene::SetSceneType(eScene _type)
{
	sceneType = _type;
}

eScene Scene::GetSceneType()
{
	return sceneType;
}