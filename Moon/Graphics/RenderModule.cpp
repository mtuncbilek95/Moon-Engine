#include "RenderModule.h"

#include <Moon/Log/Log.h>
#include <Moon/DXDevice/DXManager.h>
#include <Moon/FileSystem/FileSystem.h>

namespace Moon
{
	RenderModule::RenderModule()
	{
	}

	bool RenderModule::CreateDeviceContext()
	{
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0, D3D11_SDK_VERSION,
			DXManager::GetInstance().GetDevice().GetAddressOf(), nullptr, DXManager::GetInstance().GetContext().GetAddressOf());

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create the D3D11 Device.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "D3D11 Device has been successfully created.");

		return true;
	}
	bool RenderModule::CreateSwapchain(const HWND p_Handle)
	{
		HRESULT hr;
		DXGI_SWAP_CHAIN_DESC swapChainDesc{};

		//  Swap chain figures out the size of the window by checking window handle
		swapChainDesc.BufferDesc.Width = 0;
		swapChainDesc.BufferDesc.Height = 0;

		//  Color Format
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

		//  Since we don't specify size, scaling is also unspecified.
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		//  Anti-aliasing
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		//  Pipeline is going to be rendering all of stuff.
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferCount = 2;

		swapChainDesc.OutputWindow = p_Handle;
		swapChainDesc.Windowed = true;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Flags = 0;

		ComPtr<IDXGIDevice> dxgiDevice;
		hr = DXManager::GetInstance().GetDevice().As(&dxgiDevice);
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to get the DXGI Device.");
			return false;
		}

		ComPtr<IDXGIAdapter> dxgiAdapter;
		hr = dxgiDevice.Get()->GetParent(IID_PPV_ARGS(dxgiAdapter.GetAddressOf()));
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to get the DXGI Adapter.");
			return false;
		}

		ComPtr<IDXGIFactory> dxgiFactory;
		hr = dxgiAdapter.Get()->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf()));
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to get the DXGI Factory.");
			return false;
		}

		hr = dxgiFactory->CreateSwapChain(DXManager::GetInstance().GetDevice().Get(), &swapChainDesc, &DXManager::GetInstance().GetSwapchain());

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Swapchain.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Swapchain has been successfully created.");

		return true;
	}
	bool RenderModule::CreateRenderTargetView()
	{
		ComPtr<ID3D11Texture2D> backBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC targetViewDesc{};
		HRESULT hr;

		hr = DXManager::GetInstance().GetSwapchain()->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to get the Backbuffer.");
			return false;
		}

		hr = DXManager::GetInstance().GetDevice()->CreateRenderTargetView(backBuffer.Get(), nullptr, &DXManager::GetInstance().GetRenderTargetView());
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Render Target View.");
			return false;
		}

		DXManager::GetInstance().GetContext()->OMSetRenderTargets(1u, DXManager::GetInstance().GetRenderTargetView().GetAddressOf(), nullptr);

		Log::ConsoleLog(LogType::Success, "Render Target View has been successfully created.");

		return true;
	}
	bool RenderModule::CreatePixelShader(ComPtr<ID3DBlob>& p_Blob)
	{
		ComPtr<ID3DBlob> ErrorBlob;

		const string ShaderBlob = FileSystem::GetInstance().GetData("Shaders/PixelShader.hlsl");

		D3DCompile(ShaderBlob.c_str(), ShaderBlob.length(), nullptr, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 
			0, &p_Blob, &ErrorBlob);
		if (ErrorBlob.Get() != nullptr && ErrorBlob.Get()->GetBufferPointer() != nullptr)
		{
			Log::ConsoleLog(LogType::Warning, ErrorBlob->GetBufferPointer());
		}

		HRESULT hr = DXManager::GetInstance().GetDevice()->CreatePixelShader(p_Blob->GetBufferPointer(), p_Blob->GetBufferSize(), nullptr, &m_PixelShader);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create pixel shader.");
			return false;
		}

		DXManager::GetInstance().GetContext()->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
		Log::ConsoleLog(LogType::Success, "Pixel Shader has been successfully created.");
		return true;
	}
	bool RenderModule::CreateVertexShader(ComPtr<ID3DBlob>& p_Blob)
	{
		ComPtr<ID3DBlob> ErrorBlob;

		const string ShaderBlob = FileSystem::GetInstance().GetData("Shaders/VertexShader.hlsl");

		D3DCompile(ShaderBlob.c_str(), ShaderBlob.length(), nullptr, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS,
			0, &p_Blob, &ErrorBlob);
		if (ErrorBlob.Get() != nullptr && ErrorBlob.Get()->GetBufferPointer() != nullptr)
		{
			Log::ConsoleLog(LogType::Warning, ErrorBlob->GetBufferPointer());
		}

		HRESULT hr = DXManager::GetInstance().GetDevice()->CreateVertexShader(p_Blob->GetBufferPointer(),
			p_Blob->GetBufferSize(), nullptr, &m_VertexShader);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create vertex shader.");
			return false;
		}

		DXManager::GetInstance().GetContext()->VSSetShader(m_VertexShader.Get(), nullptr, 0u);
		Log::ConsoleLog(LogType::Success, "Pixel Shader has been successfully created.");
		return true;
	}
	bool RenderModule::CreateInputLayout(ComPtr<ID3DBlob>& p_Blob)
	{
		HRESULT hr;

		const D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		hr = DXManager::GetInstance().GetDevice()->CreateInputLayout(inputElementDesc, static_cast<uint32>(std::size(inputElementDesc)),
			p_Blob->GetBufferPointer(), p_Blob->GetBufferSize(), &DXManager::GetInstance().GetInputLayout());
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Input Layout");
			return false;
		}

		DXManager::GetInstance().GetContext()->IASetInputLayout(DXManager::GetInstance().GetInputLayout().Get());

		Log::ConsoleLog(LogType::Success, "Input Layout has been successfully created.");
		return true;
	}
	bool RenderModule::CreateViewport(XMINT2 p_WindowSize)
	{
		D3D11_VIEWPORT m_Viewport{};

		if (p_WindowSize.x < 640 || p_WindowSize.y < 480)
		{
			Log::ConsoleLog(LogType::Error, "Use a windowsize bigger than 640x480");
			return false;
		}

		m_Viewport.Width = (float)p_WindowSize.x;
		m_Viewport.Height = (float)p_WindowSize.y;
		m_Viewport.MinDepth = 0;
		m_Viewport.MaxDepth = 1;
		m_Viewport.TopLeftX = 0;
		m_Viewport.TopLeftY = 0;

		DXManager::GetInstance().GetContext()->RSSetViewports(1u, &m_Viewport);

		Log::ConsoleLog(LogType::Info, "Viewport has been set.");

		return true;
	}
}