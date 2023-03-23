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

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Texture.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Texture has been created successfully.");
		return true;
	}

	bool TextureObject::CreateShaderResourceView()
	{
		m_ShaderResourceDesc.Format = m_TextureBufferDesc.Format;
		m_ShaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		m_ShaderResourceDesc.Texture2D.MostDetailedMip = 0;
		m_ShaderResourceDesc.Texture2D.MipLevels = -1;

		HRESULT hr = RenderDevice::GetInstance().m_Device->CreateShaderResourceView(m_TextureBuffer.Get(), &m_ShaderResourceDesc, &m_ShaderResourceView);
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, " Failed to create Shader Resource View.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Shader Resource View has been created successfully.");
		return true;
	}

	bool TextureObject::CreateSamplerState()
	{
		D3D11_SAMPLER_DESC SamplerDesc{};
		SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.MipLODBias = 1.0f;
		SamplerDesc.MaxAnisotropy = 1;
		SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

		for (auto& el : SamplerDesc.BorderColor)
		{
			el = 0.0f;
		}

		SamplerDesc.MinLOD = 0;
		SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		
		HRESULT hr = RenderDevice::GetInstance().m_Device->CreateSamplerState(&SamplerDesc, &m_SamplerState);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Sampler State.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Sampler State has been created successfully.");

		return true;
	}

	bool TextureObject::CreateBlendState()
	{
		D3D11_BLEND_DESC blendDesc{};
		D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};

		renderTargetBlendDesc.BlendEnable = true;
		renderTargetBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		renderTargetBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
		renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
		renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
		renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		blendDesc.IndependentBlendEnable = true;
		blendDesc.AlphaToCoverageEnable = false;

		HRESULT hr = RenderDevice::GetInstance().m_Device->CreateBlendState(&blendDesc, &m_BlendState);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Blend State.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Blend State has been created successfully.");
		return true;
	}
}