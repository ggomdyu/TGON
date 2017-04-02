#include "PrecompiledHeader.h"

#include <cstdint>
#include <crtdbg.h>
#include <Windows.h>

#include "WindowsApplication.h"

#ifndef NDEBUG
	#define _CRTDBG_MAP_ALLOC
	#define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Use common control v6.0
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")


namespace tgon
{
    extern int main(int argc, char** argv);
}

namespace 
{

bool RegisterWindowClass()
{
	// This is the base form of window class.
	WNDCLASSEXW wcex {};

	wcex.cbSize = sizeof(wcex);
	wcex.lpszClassName = tgon::WindowsApplication::AppClassName;
	wcex.style = CS_DBLCLKS;
	wcex.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wcex.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wcex.hIcon = LoadIconW(nullptr, IDI_APPLICATION);
	wcex.hInstance = tgon::WindowsApplication::InstanceHandle;
	wcex.lpfnWndProc = tgon::WindowsApplication::OnMessageHandled; // Default message procedure; More fast than EvHandleMsgProc

    return RegisterClassExW(&wcex) != 0;
}

} /* namespace } */


int WINAPI WinMain(_In_ HINSTANCE instanceHandle, _In_ HINSTANCE prevInstanceHandle, _In_ LPSTR commandLine, _In_ int commandShow)
{
#ifndef NDEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Platform-independent initialization is here
	{
        tgon::WindowsApplication::EnableFloatingException(EM_OVERFLOW | EM_UNDERFLOW | EM_ZERODIVIDE);

		// TODO: Insert mini-dump setting code here

        RegisterWindowClass();
    }

	// Call the platform independent main
    tgon::main(__argc, __argv);
}