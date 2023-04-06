#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/Assets/RenderObjectDesc.h>

#include <Moon/Assets/Buffer/ConstantBufferTypes.h>

namespace Moon
{

	enum class BufferType
	{
		VertexBuffer,
		IndexBuffer,
		ConstantBuffer
	};

	class RenderObject
	{
	public:
		RenderObject();

		int GetIndexCount();

		BaseConstantBuffer& GetConstantBlob();

		ComPtr<ID3D11Buffer>& GetBuffer(BufferType p_BufferType);

		bool CreateVertexBuffer();
		bool CreateIndexBuffer();
		bool CreateConstantBuffer();

	private:
		ComPtr<ID3D11Buffer> m_VertexBuffer;
		ComPtr<ID3D11Buffer> m_IndexBuffer;
		ComPtr<ID3D11Buffer> m_ConstantBuffer;

	private:
		std::vector<ObjectData> m_Vertices;
		std::vector<int> m_Indices;

		BaseConstantBuffer m_CBufferBlob;
	};
}
