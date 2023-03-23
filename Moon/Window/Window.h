#pragma once

#include <Moon/Core/MoonCore.h>
#include <Moon/Window/WindowCore.h>

namespace Moon
{
	class Window
	{
	public:
		Window(int p_Width, int p_Height);

		Window(const Window&) = delete;
		Window& operator= (const Window&) = delete;
		~Window();

		void InitializeWindow();
		bool ProcessMessage();

		void SetIsRunning(bool p_IsRunning);
		bool GetIsRunning();

		XMINT2 GetWindowSize();
		HWND GetWindowHandler();

	protected:
		static LRESULT APIENTRY WindowProc(HWND p_WindowHandle, UINT message, WPARAM wParam, LPARAM lParam);

	private:
		HINSTANCE m_HandleInstance;
		HWND m_WindowHandle;

		XMINT2 m_WindowSize;

		const string m_ClassName;
		const string m_WindowName;

		bool b_IsRunning;
	};
}