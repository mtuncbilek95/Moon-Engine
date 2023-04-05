#include "ApplicationModule.h"

namespace Moon
{
	ApplicationModule::ApplicationModule(XMINT2 p_WindowSize)
	{
		m_Window = new Window(p_WindowSize.x, p_WindowSize.y);
	}
	void ApplicationModule::StartApplication()
	{
		m_Window->InitializeWindow();

		if(m_Window->GetWindowHandler() != nullptr)
			m_RenderManager = new RenderManager();

		m_Window->SetIsRunning(m_RenderManager->Begin(m_Window->GetWindowHandler(), m_Window->GetWindowSize()));
	}
	void ApplicationModule::LoopApplication()
	{
		while (m_Window->GetIsRunning())
		{
			if (m_Window->ProcessMessage())
			{

			}
			else
			{
				m_RenderManager->Render();
			}
		}
	}
}