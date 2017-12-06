#include "PrecompiledHeader.pch"
#include "WindowsApplication.h"

#include "WindowsWindow.h"

namespace tgon
{
namespace platform
{
namespace windows
{

WindowsApplication::WindowsApplication(const std::shared_ptr<BaseWindow>& mainWindow) :
    BaseApplication(mainWindow)
{
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

    this->OnWillTerminate();
}

void WindowsApplication::ShowMessageBox(const char* title, const char* message, MessageBoxType messageBoxType)
{
    static constexpr const LONG nativeMessageBoxTypeArray[2] =
    {
        MB_ICONQUESTION,
        MB_ICONEXCLAMATION,
    };

    // todo: ���߿� �Ķ���ͷ� utf8�� �ް��� �� utf16���� ��ȯ�ؼ�, MessageBoxW�Լ��� ó���ϵ��� �ؾ��� ��.
    // �ϴ� icu ���̺귯�� ���̴°� �ñ���.
    MessageBoxA(nullptr, message, title, nativeMessageBoxTypeArray[static_cast<int>(messageBoxType)] | MB_OK);
}

LRESULT CALLBACK WindowsApplication::OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam)
{
    auto extraMemAsWindow = reinterpret_cast<windows::WindowsWindow*>(GetWindowLongPtrW(wndHandle, GWLP_USERDATA));
    if (extraMemAsWindow)
    {
        return extraMemAsWindow->OnHandleMessage(wndHandle, message, wParam, lParam);
    }

    return DefWindowProc(wndHandle, message, wParam, lParam);
}

<<<<<<< HEAD
=======
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
	wcex.lpfnWndProc = WindowsApplication::OnHandleMessage;

	return RegisterClassExW(&wcex) != 0;
}

>>>>>>> 9e432bd77dd28cb655802278389d8517d3e18c16
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