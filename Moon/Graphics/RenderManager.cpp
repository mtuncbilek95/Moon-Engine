#include "RenderManager.h"

#include <Moon/Graphics/RenderCore.h>

#include <Moon/Log/Log.h>
#include <Moon/Graphics/RenderModule.h>
#include <Moon/DXDevice/DXManager.h>
#include <Moon/Assets/RenderObject.h>

namespace Moon
{
	RenderModule* RenderManager::m_RenderModule = nullptr;

	RenderManager::RenderManager()
	{
		if (!m_RenderModule)
			m_RenderModule = new RenderModule();
	}
	RenderModule& RenderManager::GetInstance()
	{
		if (!m_RenderModule)
			m_RenderModule = new RenderModule();
		return *m_RenderModule;
	}
	bool RenderManager::Begin(const HWND p_Handle, XMINT2 p_WindowSize)
	{
		ComPtr<ID3DBlob> shaderBlob;

		if (!GetInstance().CreateDeviceContext())
			return false;
		if (!GetInstance().CreateSwapchain(p_Handle))
			return false;
		if (!GetInstance().CreateRenderTargetView())
			return false;
		if (!GetInstance().CreateViewport(p_WindowSize))
			return false;
		if (!GetInstance().CreatePixelShader(shaderBlob))
			return false;
		if (!GetInstance().CreateVertexShader(shaderBlob))
			return false;
		if (!GetInstance().CreateInputLayout(shaderBlob))
			return false;

		return true;
	}

	void RenderManager::Render()
	{
		const float clearColor[] = { 0.084f, 0.106f, 0.122f, 1.0f };
		DXManager::GetInstance().GetContext()->ClearRenderTargetView(DXManager::GetInstance().GetRenderTargetView().Get(), clearColor);

		for (auto& object : m_RenderObjects)
		{
			DXManager::GetInstance().GetContext()->DrawIndexed(object->GetIndexCount(), 0u, 0u);
		}

		DXManager::GetInstance().GetSwapchain()->Present(1, 0);
	}
}