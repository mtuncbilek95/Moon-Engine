#pragma once

#include <Moon/Window/Window.h>
#include <Moon/Graphics/RenderManager.h>

namespace Moon
{
	class Window;
	class RenderManager;
	class SceneManager;

	class ApplicationModule
	{
	public:
		ApplicationModule(XMINT2 p_WindowSize);

		void StartApplication();
		void LoopApplication();

	private:
		Window* m_Window;
		RenderManager* m_RenderManager;
	};
}