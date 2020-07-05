#include "PrecompiledHeader.h"

#ifndef NDEBUG
#include <crtdbg.h>
#endif

#include "../Application.h"

#ifndef NDEBUG
#   define _CRTDBG_MAP_ALLOC
#   define new new (_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

int WINAPI WinMain([[maybe_unused]] HINSTANCE instanceHandle, [[maybe_unused]] HINSTANCE prevInstanceHandle, [[maybe_unused]] LPSTR commandLine, [[maybe_unused]] int commandShow)
{
#ifndef NDEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    decltype(auto) application = tg::Application::GetInstance();
    application.Initialize();
    application.MessageLoop();

    return 0;
}