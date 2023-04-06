#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/EntityComponent/EntityCore.h>

#include <Moon/EntityComponent/Component.h>
#include <Moon/Assets/Buffer/ConstantBufferTypes.h>
#include <Moon/Assets/SpriteObject.h>

#include <Moon/DXDevice/DXManager.h>

namespace Moon
{
	class SpriteRenderer : public Component
	{
		friend class SpriteAnimation;
	public:
		SpriteRenderer() : Component()
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

			GetEntity()->GetRenderObject()->GetConstantBlob().AtlasPoint = m_CurrSprite->GetShaderBufferPoint();

			D3D11_MAPPED_SUBRESOURCE cbSubresource{};
			DXManager::GetInstance().GetContext()->Map(GetEntity()->GetRenderObject()->GetBuffer(BufferType::ConstantBuffer).Get(), 
				0, D3D11_MAP_WRITE_DISCARD, 0, &cbSubresource);
			memcpy(cbSubresource.pData, &GetEntity()->GetRenderObject()->GetConstantBlob(), 16u);
			DXManager::GetInstance().GetContext()->Unmap(GetEntity()->GetRenderObject()->GetBuffer(BufferType::ConstantBuffer).Get(), 0);
		}

		void DrawSprite(SpriteObject* r_CurrSprite)
		{
			m_CurrSprite = r_CurrSprite;
		}
	private:
		SpriteObject* m_CurrSprite;
	};
}
