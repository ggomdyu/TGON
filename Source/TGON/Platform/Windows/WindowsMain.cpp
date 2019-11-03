#include "PrecompiledHeader.h"

#ifndef NDEBUG
#   include <crtdbg.h>
#endif

#include "Platform/Application.h"

#include "Windows.h"

#ifndef NDEBUG
#   define _CRTDBG_MAP_ALLOC
#   define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// Use common control v6.0
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE prevInstanceHandle, LPSTR commandLine, int commandShow)
{
#ifndef NDEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    using namespace tgon;

    // Initialize singleton objects.
    Application& application = Application::GetInstance();

    application.OnLaunch();
    {
        application.MessageLoop();
    }
    application.OnTerminate();

    return 0;
}