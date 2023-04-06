#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/EntityComponent/Entity.h>

namespace Moon
{
	class EntityManager
	{
	public:
		EntityManager() {}

		void AddEntity(Entity* r_Entity)
		{
			m_Entities.push_back(r_Entity);
		}

		void Begin()
		{
			for (auto& entity : m_Entities)
			{
				entity->Begin();
			}
		}
		void Loop(float r_DeltaTime)
		{
			for (auto& entity : m_Entities)
			{
				entity->Loop(r_DeltaTime);
			}
		}
		void Finish()
		{
			for (auto& entity : m_Entities)
			{
				entity->Finish();
			}
		}
	private:
		std::vector<Entity*> m_Entities;
	};
}