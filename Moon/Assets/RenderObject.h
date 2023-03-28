#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/Graphics/RenderDevice.h>

namespace Moon
{
	class RenderObject
	{
	public:
		RenderObject();

	private:
		bool CreateBuffer(ComPtr<ID3D11Buffer>& r_Buffer, void* r_Data);
	private:
		ComPtr<ID3D11Buffer> m_VertexBuffer;
		ComPtr<ID3D11Buffer> m_IndexBuffer;
		ComPtr<ID3D11Buffer> m_ConstantBuffer;
	};
}