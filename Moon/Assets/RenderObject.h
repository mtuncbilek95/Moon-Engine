#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/Assets/RenderObjectDesc.h>

namespace Moon
{
	class RenderObject
	{
	public:
		RenderObject();

	private:
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
	};
}