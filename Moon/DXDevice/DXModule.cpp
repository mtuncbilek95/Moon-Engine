#include "DXModule.h"

namespace Moon
{
	DXModule::DXModule()
	{
	}
	ComPtr<ID3D11Device>& DXModule::GetDevice()
	{
		return m_Device;
	}
	ComPtr<ID3D11DeviceContext>& DXModule::GetContext()
	{
		return m_Context;
	}
	ComPtr<IDXGISwapChain>& DXModule::GetSwapchain()
	{
		return m_Swapchain;
	}
	ComPtr<ID3D11RenderTargetView>& DXModule::GetRenderTargetView()
	{
		return m_RenderTargetView;
	}
	ComPtr<ID3D11InputLayout>& DXModule::GetInputLayout()
	{
		return m_InputLayout;
	}
}