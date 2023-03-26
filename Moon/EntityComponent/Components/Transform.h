#pragma once

#include <EntityComponent/Component.h>

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

	virtual bool Initialize() override final { return Component::Initialize(); }
	virtual void UpdateMatrix() override final { /* Will update matrix */ }

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
		UpdateMatrix();
	}

	void SetRotation(float rotation)
	{
		m_Rotation = rotation;
		UpdateMatrix();
	}

	void SetScale(XMFLOAT2 scale)
	{
		m_Scale = scale;
		UpdateMatrix();
	}

	void Move(XMFLOAT2 offsetPosition)
	{
		m_Position.x += offsetPosition.x;
		m_Position.y += offsetPosition.y;
		UpdateMatrix();
	}

	void Rotate(float offsetRotation)
	{
		m_Rotation += offsetRotation;
		UpdateMatrix();
	}
private:
	XMFLOAT2 m_Position{};
	XMFLOAT2 m_Scale{};
	float m_Rotation;
};