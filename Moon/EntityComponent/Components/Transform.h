#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/EntityComponent/Component.h>
#include <Moon/Assets/ConstantBufferTypes.h>

namespace Moon
{
	class Transform : public Component
	{
	public:
		Transform(string p_ComponentName) : Component()
		{
			m_Position = { 0.0f,0.0f };
			m_Scale = { 1.0f,1.0f };
			m_Rotation = 0.0f;
			m_ComponentName = p_ComponentName;
		}

		Transform(XMFLOAT2 position, XMFLOAT2 scale, float rotation) : Component()
		{
			m_Position = position;
			m_Scale = scale;
			m_Rotation = rotation;
		}

		virtual ~Transform() override {}

		virtual bool Initialize() override final
		{
			return Component::Initialize();
		}

		virtual void Update() override final
		{
			
		}

		XMFLOAT2 GetPosition()
		{
			return m_Position;
		}

		float GetRotation()
		{
			return m_Rotation;
		}

		void SetPosition(XMFLOAT2 position)
		{
			m_Position = position;
			Update();
		}

		void SetRotation(float rotation)
		{
			m_Rotation = rotation;
			Update();
		}

		void SetScale(XMFLOAT2 scale)
		{
			m_Scale = scale;
			Update();
		}

		void Move(XMFLOAT2 offsetPosition)
		{
			m_Position.x += offsetPosition.x;
			m_Position.y += offsetPosition.y;
			Update();
		}

		void Rotate(float offsetRotation)
		{
			m_Rotation += offsetRotation;
			Update();
		}
	private:
		XMFLOAT2 m_Position{};
		XMFLOAT2 m_Scale{};
		float m_Rotation;

	private:
		ModelMatrix m_ModelMatrix;
	};
}