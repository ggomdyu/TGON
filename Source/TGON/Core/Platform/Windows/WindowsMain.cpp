#include "PrecompiledHeader.pch"

#include <crtdbg.h>

#include "WindowsApplication.h"
#include "WindowsWindow.h"

#ifndef NDEBUG
#   define _CRTDBG_MAP_ALLOC
#   define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Use common control v6.0
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace tgon
{
namespace platform
{

extern std::shared_ptr<BaseApplication> MakeApplication();

namespace
{

std::shared_ptr<tgon::platform::windows::WindowsApplication> g_application;

/* @brief   Register WNDCLASS which has Default window property given by engine. */
bool RegisterWindowClass(HINSTANCE instanceHandle)
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(wcex);
    wcex.lpszClassName = L"TGON";
    wcex.style = CS_DBLCLKS;
    wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    wcex.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcex.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
    wcex.hInstance = instanceHandle;
    wcex.lpfnWndProc = windows::WindowsApplication::OnHandleMessage;

    return RegisterClassExW(&wcex) != 0;
}

} /* namespace */
} /* namespace platform */
} /* namespace tgon */


int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR commandLine, int commandShow)
{
#ifndef NDEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
   
    using namespace tgon::platform;

    RegisterWindowClass(instanceHandle);

    g_application = std::static_pointer_cast<windows::WindowsApplication>(MakeApplication());
    g_application->OnWillLaunch();
    {
        // 이건 WindowsMisc에 넣읍시다
	    //windows::EnableFloatException(EM_OVERFLOW | EM_UNDERFLOW | EM_ZERODIVIDE);
    }
    g_application->OnDidLaunch();

    g_application->MessageLoop();
    return 0;
}