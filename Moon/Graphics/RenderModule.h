#pragma once

#include <Moon/Graphics/RenderCore.h>

namespace Moon
{
	class RenderModule
	{
		friend class RenderManager;
	public:
		RenderModule();

	protected:
		bool CreateDeviceContext();
		bool CreateSwapchain(const HWND p_Handle);
		bool CreateRenderTargetView();
		bool CreatePixelShader(ComPtr<ID3DBlob>& p_Blob);
		bool CreateVertexShader(ComPtr<ID3DBlob>& p_Blob);
		bool CreateInputLayout(ComPtr<ID3DBlob>& p_Blob);
		bool CreateViewport(XMINT2 p_WindowSize);

	private:
		ComPtr<ID3D11PixelShader> m_PixelShader;
		ComPtr<ID3D11VertexShader> m_VertexShader;
	};
}