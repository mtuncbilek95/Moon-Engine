#pragma once

#include <Core/MoonCore.h>

#include <EntityComponent/EntityCore.h>

class Entity;

class Component {
public:
	Component() = default;

	virtual bool Initialize() { return true; }
	virtual void UpdateMatrix() {}
	virtual void Render() {}
	virtual ~Component() = default;

	void SetEntity(Entity* p_Entity) { m_Entity = p_Entity; }
	Entity* GetEntity() { return m_Entity; }

private:
	Entity* m_Entity;

	string m_ComponentName;
};