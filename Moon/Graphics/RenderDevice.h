#pragma once

#include <Moon/Core/MoonCore.h>

#include <Moon/Graphics/RenderCore.h>

namespace Moon
{
	typedef ComPtr<ID3D11Buffer> GeneralBuffer;

	class RenderDevice
	{
		friend class TextureObject;
	public:
		static RenderDevice& GetInstance();

		bool Initialize(const HWND p_Handle, XMINT2 p_WindowSize);
		void Render();
		void Refresh();

	public:
		ComPtr<ID3D11DeviceContext> GetContext() { return m_Context; }
		ComPtr<ID3D11Device> GetDevice() { return m_Device; }

	protected:
		bool CreateDeviceContext();
		bool CreateSwapchain(const HWND p_Handle);
		bool CreateRenderTargetView();
		bool CreatePixelShader(ComPtr<ID3DBlob>& p_Blob);
		bool CreateVertexShader(ComPtr<ID3DBlob>& p_Blob);
		bool CreateInputLayout(ComPtr<ID3DBlob>& p_Blob);
		bool CreateViewport(XMINT2 p_WindowSize);

	private:
		RenderDevice();
		static RenderDevice* m_RenderDevice;

	private:
		ComPtr<ID3D11Device> m_Device;
		ComPtr<ID3D11DeviceContext> m_Context;
		ComPtr<IDXGISwapChain> m_Swapchain;
		ComPtr<ID3D11RenderTargetView> m_RenderTargetView;
		ComPtr<ID3D11InputLayout> m_InputLayout;

	private:
		ComPtr<ID3D11PixelShader> m_PixelShader;
		ComPtr<ID3D11VertexShader> m_VertexShader;
	};
}