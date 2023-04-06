#pragma once 

#include <Moon/Core/MoonCore.h>

namespace Moon
{
	class EntityManager;

	class SceneObject
	{
	public:
		SceneObject();

		virtual void Begin();
		virtual void Loop(float r_DeltaTime);
		virtual void Finish();

		string GetSceneName();
	protected:
		string m_SceneName;
		EntityManager* m_EntityManager;
	};
}