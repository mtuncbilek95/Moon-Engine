#include "TextureObject.h"

#include <Libs/Stbi/stb_image.h>

#include <Moon/FileSystem/FileSystem.h>
#include <Moon/Log/Log.h>
#include <Moon/Graphics/RenderDevice.h>

namespace Moon
{
	TextureObject::TextureObject()
	{
	}

	TextureObject::~TextureObject()
	{
		delete m_ImageData;
	}

	void TextureObject::LoadTextureImage(string r_PathName)
	{
		int imageChannels{}, desiredChannels{ 4 };
		string filePath = FileSystem::GetInstance().GetGameDir() + r_PathName;
		m_ImageData = stbi_load(filePath.c_str(), &m_TotalSize.x, &m_TotalSize.y, &imageChannels, desiredChannels);

		if (m_ImageData == nullptr)
		{
			Log::ConsoleLog(LogType::Info, "Image has not been loaded.");
		}
		else
		{
			Log::ConsoleLog(LogType::Info, "Image has been loaded.");
		}
	}

	bool TextureObject::CreateTexture()
	{
		int imagePitch = 4 * sizeof(byte) * m_TotalSize.x;

		m_TextureBufferDesc.Width = m_TotalSize.x;
		m_TextureBufferDesc.Height = m_TotalSize.y;
		m_TextureBufferDesc.MipLevels = 1;
		m_TextureBufferDesc.ArraySize = 1;
		m_TextureBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		m_TextureBufferDesc.SampleDesc.Count = 1;
		m_TextureBufferDesc.SampleDesc.Quality= 0;
		m_TextureBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		m_TextureBufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SUBRESOURCE_DATA TextureResourceData{};
		TextureResourceData.pSysMem = m_ImageData;
		TextureResourceData.SysMemPitch = imagePitch;

		HRESULT hr = RenderDevice::GetInstance().m_Device->CreateTexture2D(&m_TextureBufferDesc, &TextureResourceData, &m_TextureBuffer);
	}

	bool TextureObject::CreateShaderResourceView()
	{
		return false;
	}

	bool TextureObject::CreateSamplerState()
	{
		return false;
	}

	bool TextureObject::CreateBlendState()
	{
		return false;
	}
}