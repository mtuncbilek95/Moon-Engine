#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/Graphics/RenderCore.h>

namespace Moon
{
	class RenderModule;
	class RenderObject;

	class RenderManager
	{
	public:
		RenderManager();

		static RenderModule& GetInstance();

		bool Begin(const HWND p_Handle, XMINT2 p_WindowSize);
		void Render();
 
	private:
		static RenderModule* m_RenderModule;

	private:
		std::vector<RenderObject*> m_RenderObjects;
	};
}