#include "PrecompiledHeader.pch"
#include "../Application.h"
#include "../ApplicationType.h"

#include <Windows.h>

#include "Core/Platform/Window.h"
#include "Core/Platform/WindowType.h"

namespace tgon
{
namespace platform
{
namespace
{

/* @brief   Register WNDCLASS which has Default window property given by engine. */
bool RegisterWindowClass()
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(wcex);
    wcex.lpszClassName = L"TGON";
    wcex.style = CS_DBLCLKS;
    wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
    wcex.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
    wcex.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.lpfnWndProc = Application::OnHandleMessage;

    return RegisterClassExW(&wcex) != 0;
}

} /* namespace*/

Application::Application(const WindowStyle& windowStyle)
{
    RegisterWindowClass();

    this->Initialize(windowStyle);
}

void Application::Initialize(const WindowStyle& windowStyle)
{
    m_mainWindow = std::make_shared<Window>(windowStyle);
}

void Application::MessageLoop()
{
    MSG msg {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            ::DispatchMessageW(&msg);
        }
        else
        {
            this->OnUpdate();
        }
    }

    this->OnWillTerminate();
}

void Application::ShowMessageBox(const char* title, const char* message, MessageBoxIconType messageBoxType) const
{
    static constexpr const LONG nativeMessageBoxTypeArray[2] =
    {
        MB_ICONQUESTION,
        MB_ICONEXCLAMATION,
    };

    // todo: ���߿� �Ķ���ͷ� utf8�� �ް��� �� utf16���� ��ȯ�ؼ�, MessageBoxW�Լ��� ó���ϵ��� �ؾ��� ��.
    // �ϴ� icu ���̺귯�� ���̴°� �ñ���.
    ::MessageBoxA(nullptr, message, title, nativeMessageBoxTypeArray[static_cast<int>(messageBoxType)] | MB_OK);
}


LRESULT CALLBACK Application::OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    auto extraMemAsWindow = reinterpret_cast<Window*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
    if (extraMemAsWindow)
    {
        return extraMemAsWindow->OnHandleMessage(wndHandle, message, wParam, lParam);
    }

    return DefWindowProc(wndHandle, message, wParam, lParam);
}

void Application::Terminate()
{
    ::PostQuitMessage(0);
}

const BatteryState Application::GetBatteryState() const
{
	::SYSTEM_POWER_STATUS sps;
	::GetSystemPowerStatus(&sps);

    return BatteryState(
        sps.BatteryFlag == 128 ? false : true, // hasBattery
        sps.BatteryFlag == 1 ? true : false, // isCharging
        sps.BatteryLifePercent // batteryPercentage
    );
}

} /* namespace platform */
} /* namespace tgon */
