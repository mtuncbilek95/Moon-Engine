#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/World/SceneObject.h>

namespace Moon
{
	class SceneModule
	{
	public:
		SceneModule();

		void AddNewScene(SceneObject* r_Scene);
		void SelectSceneByName(string r_SceneName);
		void SelectSceneByIndex(uint8 r_Index);
		SceneObject* GetSelectScene();

	private:
		SceneObject* m_SelectedScene;
		std::vector<SceneObject*> m_Scenes;
	};
}