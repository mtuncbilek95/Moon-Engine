#pragma once

#include <Core/MoonCore.h>
#include <EntityComponent/EntityCore.h>

class Entity
{
public:
	Entity()
	{
		for (auto& el : m_ComponentList)
		{
			el = nullptr;
		}
	}
	virtual ~Entity() {}

	virtual void Begin() {}
	virtual void Loop() {}
	virtual void Finish() {}

public:
	template<typename T, typename... TArgs>
	inline T* AddComponent(TArgs&&... args)
	{
		T* component = new T(args...);

		m_Components.emplace_back(std::move(component));

		if (component->Initialize())
		{
			m_ComponentList[ComponentBase::GetComponentTypeID<T>()] = component;
			m_ComponentBitset[ComponentBase::GetComponentTypeID<T>()] = true;
			component->SetEntity(this);
			return component;
		}

		return static_cast<T*>(nullptr);
	}
	template<typename T>
	inline T* GetComponent(std::string p_ComponentName)
	{
		for (auto el : m_Components)
			if (el->GetName() == p_ComponentName)
				return static_cast<T*>(el);
			else
			{
				T* nullComponent = new T("EmptyComponent");
				std::cout << "There is no component such as " << p_ComponentName << ".\n";
				return nullComponent;
			}
		return nullptr;
	}

	template<typename T>
	bool HasComponent() const
	{
		return m_ComponentBitset[ComponentBase::GetComponentTypeID<T>()];
	}
	bool HasAnyComponent() const
	{
		return m_ComponentBitset.any();
	}

private:
	std::vector<Component*> m_Components;

private:
	std::bitset<32> m_ComponentBitset;
	std::array<Component*, 32> m_ComponentList{};
};
