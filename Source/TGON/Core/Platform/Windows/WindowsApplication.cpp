#include "PrecompiledHeader.pch"
#include "WindowsApplication.h"

#include "WindowsWindow.h"

namespace tgon
{
namespace platform
{
namespace windows
{
WindowsApplication::WindowsApplication()
{
    this->RegisterWindowClass(GetModuleHandleW(nullptr));
}

void WindowsApplication::MessageLoop()
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
            this->OnDraw();
        }
    }

    this->OnTerminate();
}

LRESULT CALLBACK WindowsApplication::OnMessageHandled(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    auto extraMemAsWindow = reinterpret_cast<windows::WindowsWindow*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
    if (extraMemAsWindow)
    {
        return extraMemAsWindow->OnHandleMessage(wndHandle, message, wParam, lParam);
    }

    return DefWindowProc(wndHandle, message, wParam, lParam);
}

bool WindowsApplication::RegisterWindowClass(HINSTANCE instanceHandle)
{
	WNDCLASSEXW wcex{};
	wcex.cbSize = sizeof(wcex);
	wcex.lpszClassName = L"TGON";
	wcex.style = CS_DBLCLKS;
	wcex.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
	wcex.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);
	wcex.hIcon = ::LoadIconW(nullptr, IDI_APPLICATION);
	wcex.hInstance = instanceHandle;
	wcex.lpfnWndProc = WindowsApplication::OnMessageHandled;

	return RegisterClassExW(&wcex) != 0;
}

//BatteryProperty WindowsSystem::GetPowerInfo()
//{
//	SYSTEM_POWER_STATUS sps;
//	::GetSystemPowerStatus(&sps);

//	BatteryProperty adapter{
//		sps.BatteryFlag == 128 ? false : true,
//		sps.BatteryLifePercent
//	};

//	return adapter;
//}

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */