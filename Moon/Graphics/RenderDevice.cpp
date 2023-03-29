#include "RenderDevice.h"

#include <Moon/Log/Log.h>
#include <Moon/FileSystem/FileSystem.h>
#include <Moon/Assets/RenderObject.h>
namespace Moon
{
	RenderDevice* RenderDevice::m_RenderDevice = nullptr;
	
	RenderDevice::RenderDevice()
	{
		Log::ConsoleLog(LogType::Display, "********** Render Device**********");
	}

	RenderDevice& RenderDevice::GetInstance()
	{
		if (m_RenderDevice == nullptr)
			m_RenderDevice = new RenderDevice();
		return *m_RenderDevice;
	}

	bool RenderDevice::Initialize(const HWND p_Handle, XMINT2 p_WindowSize)
	{
		if (!CreateDeviceContext())
			return false;
		if (!CreateSwapchain(p_Handle))
			return false;
		if (!CreateRenderTargetView())
			return false;
		if (!CreateViewport(p_WindowSize))
			return false;
		return true;
	}

	void RenderDevice::Render()
	{
		const float clearColor[] = { 0.084f, 0.106f, 0.122f, 1.0f };
		m_Context->ClearRenderTargetView(m_RenderTargetView.Get(), clearColor);

		for (auto renderObject : m_RenderableObjects)
		{
			const uint32 stride = sizeof(ObjectData);
			const uint32 offset = 0u;

			m_Context->IASetVertexBuffers(0u, 1u, renderObject->m_VertexBuffer.GetAddressOf(), &stride, &offset);
			m_Context->IASetIndexBuffer(renderObject->m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
			m_Context->VSSetConstantBuffers(0, 1u, renderObject->m_ConstantBuffer.GetAddressOf());

			m_Context->DrawIndexed(renderObject->GetIndexCount(), 0u, 0u);
		}

		m_Swapchain->Present(1, 0);
	}

	void RenderDevice::AddRenderObject(RenderObject* r_RenderObject)
	{
		m_RenderableObjects.push_back(r_RenderObject);
	}

	bool RenderDevice::CreateDeviceContext()
	{
		HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0,
			D3D11_SDK_VERSION, m_Device.GetAddressOf(), nullptr, m_Context.GetAddressOf());

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create the D3D11 Device.");
			return false;
		}

		Log::ConsoleLog(LogType::Error, "D3D11 Device has been successfully created.");

		return true;
	}

	bool RenderDevice::CreateSwapchain(const HWND p_Handle)
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
		hr = m_Device.As(&dxgiDevice);
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
		hr = dxgiAdapter.Get()->GetParent(IID_PPV_ARGS(dxgiAdapter.GetAddressOf()));
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to get the DXGI Factory.");
			return false;
		}

		hr = dxgiFactory->CreateSwapChain(m_Device.Get(), &swapChainDesc, &m_Swapchain);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Swapchain.");
			return false;
		}

		Log::ConsoleLog(LogType::Success, "Swapchain has been successfully created.");

		return true;
	}

	bool RenderDevice::CreateRenderTargetView()
	{
		ComPtr<ID3D11Texture2D> backBuffer;
		D3D11_RENDER_TARGET_VIEW_DESC targetViewDesc{};
		HRESULT hr;

		hr = m_Swapchain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf()));
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to get the Backbuffer.");
			return false;
		}

		hr = m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTargetView);
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Render Target View.");
			return false;
		}

		m_Context->OMSetRenderTargets(1u, m_RenderTargetView.GetAddressOf(), nullptr);

		Log::ConsoleLog(LogType::Success, "Render Target View has been successfully created.");

		return true;
	}

	bool RenderDevice::CreatePixelShader(ComPtr<ID3DBlob>& Blob)
	{
		ComPtr<ID3DBlob> ErrorBlob;

		const string ShaderBlob = FileSystem::GetInstance().GetData("Shaders/PixelShader.hlsl");

		D3DCompile(ShaderBlob.c_str(), ShaderBlob.length(), nullptr, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);
		if (ErrorBlob.Get() != nullptr && ErrorBlob.Get()->GetBufferPointer() != nullptr)
		{
			Log::ConsoleLog(LogType::Warning, ErrorBlob->GetBufferPointer());
		}

		HRESULT hr = m_Device->CreatePixelShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &m_PixelShader);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create pixel shader.");
			return false;
		}

		m_Context->PSSetShader(m_PixelShader.Get(), nullptr, 0u);
		Log::ConsoleLog(LogType::Success, "Pixel Shader has been successfully created.");
		return true;
	}

	bool RenderDevice::CreateVertexShader(ComPtr<ID3DBlob>& Blob)
	{
		ComPtr<ID3DBlob> ErrorBlob;

		const string ShaderBlob = FileSystem::GetInstance().GetData("Shaders/VertexShader.hlsl");

		D3DCompile(ShaderBlob.c_str(), ShaderBlob.length(), nullptr, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &Blob, &ErrorBlob);
		if (ErrorBlob.Get() != nullptr && ErrorBlob.Get()->GetBufferPointer() != nullptr)
		{
			Log::ConsoleLog(LogType::Warning, ErrorBlob->GetBufferPointer());
		}

		HRESULT hr = m_Device->CreateVertexShader(Blob->GetBufferPointer(), Blob->GetBufferSize(), nullptr, &m_VertexShader);

		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create vertex shader.");
			return false;
		}

		m_Context->VSSetShader(m_VertexShader.Get(), nullptr, 0u);
		Log::ConsoleLog(LogType::Success, "Pixel Shader has been successfully created.");
		return true;

		return false;
	}

	bool RenderDevice::CreateInputLayout(ComPtr<ID3DBlob>& Blob)
	{
		HRESULT hr;

		const D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		hr = m_Device->CreateInputLayout(inputElementDesc, static_cast<uint32>(std::size(inputElementDesc)), Blob->GetBufferPointer(), Blob->GetBufferSize(), &m_InputLayout);
		if (FAILED(hr))
		{
			Log::ConsoleLog(LogType::Error, "Failed to create Input Layout");
			return false;
		}

		m_Context->IASetInputLayout(m_InputLayout.Get());

		Log::ConsoleLog(LogType::Success, "Input Layout has been successfully created.");
		return true;
	}

	bool RenderDevice::CreateViewport(XMINT2 p_WindowSize)
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

		m_Context->RSSetViewports(1u, &m_Viewport);

		Log::ConsoleLog(LogType::Info, "Viewport has been set.");

		return true;
	}
}