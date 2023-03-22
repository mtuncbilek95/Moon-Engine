#pragma once

#include <Core/MoonCore.h>

#include <Graphics/RenderCore.h>

namespace Moon {

	typedef ComPtr<ID3D11Buffer> GeneralBuffer;

	class RenderDevice {
	public:
		static RenderDevice& GetInstance();
	
		bool Initialize(const HWND p_Handle, XMINT2 p_WindowSize);
		void Render();
		void Refresh();

	protected:
		bool CreateDeviceContext();
		bool CreateSwapchain(const HWND p_Handle);
		bool CreateRenderTargetView();
		bool CreatePixelShader(ComPtr<ID3DBlob>& Blob);
		bool CreateVertexShader(ComPtr<ID3DBlob>& Blob);
		bool CreateInputLayout(ComPtr<ID3DBlob>& Blob);
		bool CreateViewport(XMINT2 p_WindowSize);

	private:
		static RenderDevice* m_RenderDevice;
	private:
		ComPtr<ID3D11Device> m_Device;
		ComPtr<ID3D11DeviceContext> m_Context;
		ComPtr<IDXGISwapChain> m_Swapchain;
		ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		ComPtr<ID3D11InputLayout> m_InputLayout;
	};
}