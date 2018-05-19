#include "PrecompiledHeader.h"

#ifndef NDEBUG
#   include <crtdbg.h>
#endif
#include <Windows.h>

#include "../Application.h"

#ifndef NDEBUG
#   define _CRTDBG_MAP_ALLOC
#   define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Use common control v6.0
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

namespace tgon
{
namespace
{

std::shared_ptr<Application> g_application;

} /* namespace */

extern std::shared_ptr<Application> MakeApplication();

const std::shared_ptr<Application>& Application::GetInstance()
{
    return g_application;
}

} /* namespace tgon */

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR commandLine, int commandShow)
{
#ifndef NDEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
   
    using namespace tgon;

    g_application = MakeApplication();
    g_application->OnWillLaunch();
    {
        // 이건 WindowsMisc에 넣읍시다
	    //windows::EnableFloatException(EM_OVERFLOW | EM_UNDERFLOW | EM_ZERODIVIDE);
    }
    g_application->OnDidLaunch();

    g_application->MessageLoop();
    return 0;
}