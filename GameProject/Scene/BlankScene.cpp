#include "BlankScene.h"

#include <Moon/EntityComponent/EntityManager.h>

BlankScene::BlankScene() : SceneObject()
{
	m_SceneName = "Blank Scene";
	m_EntityManager = new Moon::EntityManager();
}

void BlankScene::Begin()
{
	m_EntityManager->Begin();
}

void BlankScene::Loop(float r_DeltaTime)
{
	m_EntityManager->Loop(r_DeltaTime);
}

void BlankScene::Finish()
{
	m_EntityManager->Finish();
}
