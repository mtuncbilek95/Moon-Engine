#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/EntityComponent/EntityCore.h>

#include <Moon/Assets/TextureObject.h>
#include <Moon/Assets/SpriteObjectData.h>

namespace Moon
{
	class SpriteObject
	{
		SpriteObject(XMINT2 r_TexturePoint, TextureObject* r_TextureObject)
		{
			r_TextureObject->m_AtlasSpriteCount;
		}

	private:
		ComPtr<ID3D11Buffer> m_VertexBuffer;
		ComPtr<ID3D11Buffer> m_IndexBuffer;


	};
}