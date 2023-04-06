#include "BlankScene.h"

#include <Moon/EntityComponent/EntityManager.h>

#include <Characters/King.h>

BlankScene::BlankScene() : SceneObject()
{
	m_SceneName = "Blank Scene";
	m_EntityManager = new Moon::EntityManager();

	King* playerKing = new King();

	m_EntityManager->AddEntity(playerKing);
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
