#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/EnttiyComponent/EntityCore.h>

#include <Moon/EntityComponent/Component.h>
#include <Moon/Assets/ConstantBufferTypes.h>
#include <Moon/Assets/SpriteObject.h>

namespace Moon
{
	class SpriteRenderer : public Component
	{
		friend class SpriteAnimation;

		SpriteRenderer() : Component
		{
		}

		virtual bool Initialize() override
		{
			return Component::Initialize();
		}

		virtual void Update() override
		{
			Component::Update();
		}

		virtual void Render() override
		{
			Component::Render();

			
		}

	private:
		void CatchSprite(SpriteObject* r_CurrSprite)
		{
			m_CurrSprite = r_CurrSprite;
		}
	private:
		SpriteObject* m_CurrSprite;
}
