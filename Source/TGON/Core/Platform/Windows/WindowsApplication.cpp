#include "PrecompiledHeader.h"

#include "WindowsApplication.h"
#include "WindowsWindow.h"


#include <cstdint>
#include <crtdbg.h>
#include <Windows.h>

#include "WindowsApplication.h"
#include "WindowsWindow.h"
#include "Engine/Engine.h"

#ifndef NDEBUG
#   define _CRTDBG_MAP_ALLOC
#   define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Use common control v6.0
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

class F
{
public:
    int* foo() const
    {
        return m;
    }

    int* m;
};



namespace tgon
{
namespace platform
{
namespace windows
{

WindowsApplication::WindowsApplication(HINSTANCE instanceHandle) :
    m_instanceHandle(instanceHandle)
{
    this->RegisterWindowClass();
}

void WindowsApplication::Initialize(HINSTANCE instanceHandle)
{
}

WindowsApplication* WindowsApplication::Get()
{
    static WindowsApplication instance;
    return &instance;
}

bool WindowsApplication::RegisterWindowClass()
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(wcex);
    wcex.lpszClassName = L"TGON";
    wcex.style = CS_DBLCLKS;
    wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    wcex.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcex.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
    wcex.hInstance = m_instanceHandle;
    wcex.lpfnWndProc = WindowsApplication::OnHandleMessage;

    return RegisterClassExW(&wcex) != 0;
}

LRESULT CALLBACK WindowsApplication::OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    /*auto extraMemAsWindow = reinterpret_cast<windows::WindowsWindow*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
    if (extraMemAsWindow)
    {
        return extraMemAsWindow->OnHandleMessage(wndHandle, message, wParam, lParam);
    }*/

    return DefWindowProc(wndHandle, message, wParam, lParam);
}

HINSTANCE WindowsApplication::GetInstanceHandle() const noexcept
{
    return m_instanceHandle;
}

void WindowsApplication::GetLanguage(char* destBuffer, std::size_t bufferLength)
{
    ::GetLocaleInfoA(LOCALE_NAME_USER_DEFAULT, LOCALE_SISO639LANGNAME, destBuffer, bufferLength);
}

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR commandLine, int commandShow)
{
#ifndef NDEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    using namespace tgon::platform;

    windows::WindowsApplication::Get()->Initialize(instanceHandle);

    // 이건 WindowsMisc에 넣읍시다
	//windows::EnableFloatException(EM_OVERFLOW | EM_UNDERFLOW | EM_ZERODIVIDE);

	// TODO: Insert mini-dump setting code here
    
    tgon::TEngine engine;
    return engine.Execute(__argc, __argv);
}