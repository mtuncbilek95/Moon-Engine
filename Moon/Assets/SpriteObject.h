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
		SpriteObject(XMINT2 r_TexturePoint, TextureObject* r_TextureObject)
		{
			m_TextureObject = r_TextureObject;
			m_TexturePoint = r_TexturePoint;
		}
	private:
		TextureObject* m_TextureObject;
		XMINT2 m_TexturePoint;
	};
}