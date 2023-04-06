#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/EntityComponent/EntityCore.h>

namespace Moon
{
	class Entity;

	class Component
	{
	public:
		Component() : m_Entity(nullptr) {}

		virtual bool Initialize() { return true; }
		virtual void Update() {}
		virtual void Render() {}
		virtual ~Component() = default;

		void SetEntity(Entity* p_Entity) { m_Entity = p_Entity; }
		Entity* GetEntity() { return m_Entity; }

	private:
		Entity* m_Entity;

		string m_ComponentName;
	};
}