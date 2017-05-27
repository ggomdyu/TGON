#include "PrecompiledHeader.h"

#include <cstdint>
#include <crtdbg.h>
#include <Windows.h>

#include "WindowsApplication.h"
#include "WindowsWindow.h"
#include "Engine/Engine.h"

#ifndef NDEBUG
	#define _CRTDBG_MAP_ALLOC
	#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Use common control v6.0
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

using namespace tgon::platform;

namespace {

bool RegisterWindowClass()
{
    WNDCLASSEXW wcex {};
    wcex.cbSize = sizeof(wcex);
    wcex.lpszClassName = L"TGON";
    wcex.style = CS_DBLCLKS;
    wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    wcex.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcex.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
    wcex.hInstance = windows::GetInstanceHandle();
	wcex.lpfnWndProc = [](HWND wndHandle, UINT wndMsg, WPARAM wParam, LPARAM lParam)
	{
		auto extraMemAsWindow = reinterpret_cast<windows::WindowsWindow*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
		if (extraMemAsWindow)
		{
			return extraMemAsWindow->OnHandleMessage(wndHandle, wndMsg, wParam, lParam);
		}

		return DefWindowProc(wndHandle, wndMsg, wParam, lParam);
	};

    return RegisterClassExW(&wcex) != 0;
}

} /* namespace */

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR commandLine, int commandShow)
{
#ifndef NDEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	windows::EnableFloatException(EM_OVERFLOW | EM_UNDERFLOW | EM_ZERODIVIDE);

	// TODO: Insert mini-dump setting code here
    RegisterWindowClass();
    
    tgon::TEngine engine;
    return engine.Execute(__argc, __argv);
}