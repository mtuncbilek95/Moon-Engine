#include "SceneObject.h"

#include <Moon/EntityComponent/EntityManager.h>

namespace Moon
{
	SceneObject::SceneObject() : m_EntityManager(nullptr)
	{
	}

	void SceneObject::Begin()
	{
	}

	void SceneObject::Loop(float r_DeltaTime)
	{
	}

	void SceneObject::Finish()
	{
	}

	string SceneObject::GetSceneName()
	{
		return m_SceneName;
	}
}