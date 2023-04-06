#include "SceneModule.h"

#include <Moon/World/SceneObject.h>

namespace Moon
{
	SceneModule::SceneModule() : m_SelectedScene(nullptr)
	{
	}
	void SceneModule::AddNewScene(SceneObject* r_Scene)
	{
		m_Scenes.push_back(r_Scene);
	}
	void SceneModule::SelectSceneByName(string r_SceneName)
	{
		for (auto& scene : m_Scenes)
		{
			if (scene->GetSceneName() == r_SceneName)
				m_SelectedScene = scene;
		}
	}
	void SceneModule::SelectSceneByIndex(uint8 r_Index)
	{
		m_SelectedScene = m_Scenes[0];
	}
	SceneObject* SceneModule::GetSelectScene()
	{
		return m_SelectedScene;
	}
}