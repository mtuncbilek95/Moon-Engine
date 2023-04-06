#include "ApplicationModule.h"

#include <Moon/World/SceneManager.h>
#include <Moon/Timer/Timer.h>

#include <Moon/Log/Log.h>

namespace Moon
{
	ApplicationModule::ApplicationModule(XMINT2 p_WindowSize)
	{
		m_Window = new Window(p_WindowSize.x, p_WindowSize.y);
		m_RenderManager = new RenderManager();
	}
	void ApplicationModule::StartApplication()
	{
		m_Window->InitializeWindow();

		if (m_Window->GetWindowHandler())
			m_Window->SetIsRunning(m_RenderManager->Begin(m_Window->GetWindowHandler(), m_Window->GetWindowSize()));

		SceneManager::GetInstance().SelectSceneByIndex(0);
		Log::ConsoleLog(LogType::Info, SceneManager::GetInstance().GetSelectScene()->GetSceneName(), " has been loaded.");
	}
	void ApplicationModule::LoopApplication()
	{
		if(SceneManager::GetInstance().GetSelectScene())
			SceneManager::GetInstance().GetSelectScene()->Begin();

		while (m_Window->GetIsRunning())
		{
			if (m_Window->ProcessMessage())
			{
				Timer::GetInstance().Tick();
				if (SceneManager::GetInstance().GetSelectScene())
					SceneManager::GetInstance().GetSelectScene()->Loop(Timer::GetInstance().DeltaTime());
			}
			else
			{
				m_RenderManager->Render();
			}
		}

		if (SceneManager::GetInstance().GetSelectScene())
			SceneManager::GetInstance().GetSelectScene()->Finish();
	}
}