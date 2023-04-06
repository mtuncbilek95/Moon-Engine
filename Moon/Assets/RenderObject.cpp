#include "RenderObject.h"

#include <Moon/Graphics/RenderManager.h>
#include <Moon/DXDevice/DXManager.h>
#include <Moon/Log/Log.h>

namespace Moon
{
	RenderObject::RenderObject()
	{
	}

	int RenderObject::GetIndexCount()
	{
		return m_Indices.size();
	}

	BaseConstantBuffer& RenderObject::GetConstantBlob()
	{
		return m_CBufferBlob;
	}

	ComPtr<ID3D11Buffer>& RenderObject::GetBuffer(BufferType p_BufferType)
	{
		switch (p_BufferType)
		{
		case Moon::BufferType::VertexBuffer:
			return m_VertexBuffer;
			break;
		case Moon::BufferType::IndexBuffer:
			return m_IndexBuffer;
			break;
		case Moon::BufferType::ConstantBuffer:
			return m_ConstantBuffer;
			break;
		default:
			return m_VertexBuffer;
			break;
		}
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

		hr = DXManager::GetInstance().GetDevice()->CreateBuffer(&BufferDesc, &ResourceData, &m_VertexBuffer);

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

		hr = DXManager::GetInstance().GetDevice()->CreateBuffer(&BufferDesc, &ResourceData, &m_IndexBuffer);

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
		ResourceData.pSysMem = &m_CBufferBlob;

		hr = DXManager::GetInstance().GetDevice()->CreateBuffer(&BufferDesc, &ResourceData, &m_ConstantBuffer);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Constant Buffer.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Constant Buffer has been successfully created.");

		return true;
	}
}