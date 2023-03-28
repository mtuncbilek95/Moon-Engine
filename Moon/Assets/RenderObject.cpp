#include "RenderObject.h"

namespace Moon
{
	RenderObject::RenderObject()
	{
	}
	bool RenderObject::CreateBuffer(ComPtr<ID3D11Buffer>& r_Buffer, void* r_Data)
	{
		D3D11_BUFFER_DESC BufferDesc = {};
		BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.MiscFlags = 0;
		BufferDesc.ByteWidth = sizeof(uint16) * indices.size();

		BufferDesc.StructureByteStride = sizeof(uint16);

		D3D11_SUBRESOURCE_DATA IndexResourceData = {};
		IndexResourceData.pSysMem = (void*)indices.data();

		dxDevice->CreateBuffer(&IndexBufferDesc, &IndexResourceData, &m_IndexBuffer);
	}
}