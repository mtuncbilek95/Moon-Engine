#include "RenderObject.h"

#include <Moon/Graphics/RenderDevice.h>
#include <Moon/Log/Log.h>

namespace Moon
{
	RenderObject::RenderObject()
	{
		Log::ConsoleLog(LogType::Display, "********** Render Object **********");
	}

	bool RenderObject::CreateVertexBuffer()
	{
		HRESULT hr;

		D3D11_BUFFER_DESC BufferDesc{};
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.MiscFlags = 0;
		BufferDesc.ByteWidth = sizeof(ObjectData) * m_Vertices.size();
		BufferDesc.StructureByteStride = sizeof(ObjectData);

		D3D11_SUBRESOURCE_DATA ResourceData{};
		ResourceData.pSysMem = (void*)m_Vertices.data();

		hr = RenderDevice::GetInstance().GetDevice()->CreateBuffer(&BufferDesc, &ResourceData, &m_VertexBuffer);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Vertex Buffer.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Vertex Buffer has been successfully created.");

		return true;
	}

	bool RenderObject::CreateIndexBuffer()
	{
		HRESULT hr;

		D3D11_BUFFER_DESC BufferDesc{};
		BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.MiscFlags = 0;
		BufferDesc.ByteWidth = sizeof(uint16) * m_Indices.size();

		BufferDesc.StructureByteStride = sizeof(uint16);

		D3D11_SUBRESOURCE_DATA ResourceData{};
		ResourceData.pSysMem = (void*)m_Indices.data();

		hr = RenderDevice::GetInstance().GetDevice()->CreateBuffer(&BufferDesc, &ResourceData, &m_IndexBuffer);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Index Buffer.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Index Buffer has been successfully created.");

		return true;
	}

	bool RenderObject::CreateConstantBuffer()
	{
		HRESULT hr;

		D3D11_BUFFER_DESC BufferDesc{};
		BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDesc.MiscFlags = 0;
		BufferDesc.ByteWidth = 16u;
		BufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA ResourceData{};
		ResourceData.pSysMem = &constantBuffer;

		hr = RenderDevice::GetInstance().GetDevice()->CreateBuffer(&BufferDesc, &ResourceData, &m_ConstantBuffer);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Index Buffer.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Index Buffer has been successfully created.");

		return true;
	}
}