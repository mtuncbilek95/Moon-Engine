#pragma once

#include <Moon/Core/MoonCore.h>

namespace Moon
{
	class SceneObject;
	class SceneModule
	{
	public:
		SceneModule();

		void AddNewScene(SceneObject* r_Scene);
		void ChangeScene(string r_SceneName);
		SceneObject* GetSelectScene();

	private:
		SceneObject* m_SelectedScene;
		std::vector<SceneObject*> m_Scenes;
	};
}