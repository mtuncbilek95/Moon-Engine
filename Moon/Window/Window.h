#pragma once

#include <Core/MoonCore.h>
#include <Window/WindowCore.h>

namespace Moon {

	class Window {
	public:

		Window(int width, int height);

		Window(const Window&) = delete;
		Window& operator= (const Window&) = delete;
		~Window();

		void InitializeWindow();
		bool ProcessMessage();

		void SetIsRunning(bool bValue);
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