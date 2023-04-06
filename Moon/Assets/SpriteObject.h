#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/EntityComponent/EntityCore.h>

#include <Moon/Assets/TextureObject.h>

namespace Moon
{
	class SpriteObject
	{
	public:
		/**
		 * @brief Constructor for Sprite
		 * @param r_TexturePoint Vector location of the desired sprite.
		 * @param r_TextureObject Related Texture Object.
		*/
		SpriteObject(XMINT2 r_TargetPosition, TextureObject* r_TextureObject)
		{
			m_TextureObject = r_TextureObject;
			m_TexturePoint = r_TargetPosition;
		}

		TextureObject* GetTexture()
		{
			return m_TextureObject;
		}

		XMFLOAT2 GetShaderBufferPoint()
		{
			XMFLOAT2 point;
			point = { static_cast<float>(m_TexturePoint.x) / m_TextureObject->m_AtlasSpriteCount.x, 
				static_cast<float>(m_TexturePoint.y) / m_TextureObject->m_AtlasSpriteCount.y };

			return point;
		}
	private:
		TextureObject* m_TextureObject;
		XMINT2 m_TexturePoint;
	};
}