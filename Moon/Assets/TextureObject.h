#pragma once 

#include <Moon/Core/MoonCore.h>
#include <Moon/Graphics/RenderCore.h>

namespace Moon
{
	class TextureObject
	{
	public:
		TextureObject();
		~TextureObject();
	protected:
		void LoadTextureImage(string r_PathName);

		bool CreateTexture();
		bool CreateShaderResourceView();
		bool CreateSamplerState();
		bool CreateBlendState();
	private:
		XMINT2 m_TotalSize;
		const byte* m_ImageData = nullptr;

	private:
		ComPtr<ID3D11Texture2D> m_TextureBuffer;
		D3D11_TEXTURE2D_DESC m_TextureBufferDesc{};

		ComPtr<ID3D11ShaderResourceView> m_ShaderResourceView;
		D3D11_SHADER_RESOURCE_VIEW_DESC m_ShaderResourceDesc{};

		ComPtr<ID3D11SamplerState> m_SamplerState;
		ComPtr<ID3D11BlendState> m_BlendState;
	};
}