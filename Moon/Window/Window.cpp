#include "Window.h"

#include <Moon/Resources/Resource.h>
#include <Moon/Log/Log.h>

namespace Moon
{
	Window::Window(int width, int height) : m_WindowSize({ width,height }), m_HandleInstance(GetModuleHandle(nullptr)), m_WindowHandle(nullptr),
		b_IsRunning(false), m_ClassName("WindowClass"), m_WindowName("Kings and Pigs")
	{
		Log::ConsoleLog(LogType::Display, "********** Window Device **********");
	}

	Window::~Window()
	{
		UnregisterClass(m_ClassName.c_str(), m_HandleInstance);
		DestroyWindow(m_WindowHandle);
		m_HandleInstance = 0;
		m_WindowHandle = 0;
	}

	void Window::InitializeWindow()
	{

		WNDCLASSEX windowClass{};
		windowClass.cbSize = sizeof(windowClass);
		windowClass.lpszClassName = m_ClassName.c_str();
		windowClass.lpszMenuName = nullptr;
		windowClass.hInstance = m_HandleInstance;
		windowClass.hIcon = (HICON)(LoadImage(m_HandleInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 32, 32, 0));
		windowClass.hIconSm = (HICON)(LoadImage(m_HandleInstance, MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0));
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		windowClass.lpfnWndProc = WindowProc;

		RegisterClassEx(&windowClass);

		DWORD windowStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

		RECT windowSize{};
		windowSize.left = 250;
		windowSize.top = 250;
		windowSize.right = windowSize.left + m_WindowSize.x;
		windowSize.bottom = windowSize.top + m_WindowSize.y;

		AdjustWindowRect(&windowSize, windowStyle, false);

		m_WindowHandle = CreateWindowEx(0, m_ClassName.c_str(), m_WindowName.c_str(), windowStyle, windowSize.left, windowSize.top, windowSize.right - windowSize.left,
			windowSize.bottom - windowSize.top, nullptr, nullptr, m_HandleInstance, this);
		if (m_WindowHandle != nullptr)
		{
			Log::ConsoleLog(LogType::Success, "Window has been successfully created.");
			ShowWindow(m_WindowHandle, SW_SHOW);
#ifdef MOON_DEBUG
			ShowWindow(GetConsoleWindow(), SW_SHOW);
#else
			ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
		}
	}

	bool Window::ProcessMessage()
	{
		MSG msg{};

		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			return true;
		}
		else
			return false;
	}

	void Window::SetIsRunning(bool p_IsRunning)
	{
		b_IsRunning = p_IsRunning;
	}

	bool Window::GetIsRunning()
	{
		return b_IsRunning;
	}

	XMINT2 Window::GetWindowSize()
	{
		return m_WindowSize;
	}

	HWND Window::GetWindowHandler()
	{
		return m_WindowHandle;
	}

	LRESULT Window::WindowProc(HWND p_WindowHandle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_CREATE:
		{
			Window* WindowPtr = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
			SetWindowLongPtr(p_WindowHandle, GWLP_USERDATA, (LONG_PTR)WindowPtr);
			break;
		}
		case WM_CLOSE:
			((Window*)(GetWindowLongPtr(p_WindowHandle, GWLP_USERDATA)))->b_IsRunning = false;
			break;
		case WM_QUIT:
			((Window*)(GetWindowLongPtr(p_WindowHandle, GWLP_USERDATA)))->b_IsRunning = false;
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}

		return DefWindowProc(p_WindowHandle, message, wParam, lParam);
	}
}