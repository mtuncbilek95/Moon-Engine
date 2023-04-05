#pragma once

#include <Moon/Graphics/RenderCore.h>

namespace Moon
{
	class DXModule
	{
	public:
		DXModule();

		ComPtr<ID3D11Device>& GetDevice();
		ComPtr<ID3D11DeviceContext>& GetContext();
		ComPtr<IDXGISwapChain>& GetSwapchain();
		ComPtr<ID3D11RenderTargetView>& GetRenderTargetView();
		ComPtr<ID3D11InputLayout>& GetInputLayout();
		
	private:
		ComPtr<ID3D11Device> m_Device;
		ComPtr<ID3D11DeviceContext> m_Context;
		ComPtr<IDXGISwapChain> m_Swapchain;
		ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		ComPtr<ID3D11InputLayout> m_InputLayout;
	};
}