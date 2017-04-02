#include "PrecompiledHeader.h"
#include "WindowsApplication.h"

#include "WindowsWindowFrame.h"

namespace tgon
{

const HINSTANCE WindowsApplication::InstanceHandle = GetModuleHandle( nullptr );
const wchar_t* WindowsApplication::AppClassName = L"TGON";

bool WindowsApplication::PullMessage(_Out_ MSG* message)
{
    return WindowsApplication::PullMessage(nullptr, message);
}

bool WindowsApplication::PullMessage(_In_ const WindowsWindowFrame* window, _Out_ MSG* message)
{
    return PeekMessageW(message, window->GetWindowHandle(), 0, 0, PM_REMOVE) == TRUE;
}

bool WindowsApplication::PumpMessage(_Out_ MSG* message)
{
    // Get the message from queue.
	if (PeekMessageW(message, nullptr, 0, 0, PM_REMOVE) == TRUE)
	{
		// Process WM_CHAR
		//::TranslateMessage(&msg);

		// This will invke tgon::WindowsPlatformApplication::MessageProc each of events
		::DispatchMessageW(message);
		return true;
	}
	else
	{
		return false;
	}
}

void WindowsApplication::ShowMessageBox(const char* message, const char* caption)
{
    MessageBoxA(nullptr, message, caption, MB_OK);
}

void WindowsApplication::ShowMessageBox(const wchar_t* message, const wchar_t* caption)
{
    MessageBoxW(nullptr, message, caption, MB_OK);
}

LRESULT WINAPI WindowsApplication::OnMessageHandled(_In_ HWND wndHandle, _In_ UINT msg, _In_ WPARAM wParam, _In_ LPARAM lParam )
{
	WindowsWindowFrame* extraMemAsWindow = reinterpret_cast<WindowsWindowFrame*>(
		GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));
	
	if ( extraMemAsWindow )
	{
		return extraMemAsWindow->OnMessageHandled( wndHandle, msg, wParam, lParam );
	}
	else
	{
		return DefWindowProc( wndHandle, msg, wParam, lParam );
	}
}

void WindowsApplication::ExitThread( int32_t exitCode )
{
	::ExitThread(exitCode);
}

void WindowsApplication::Quit(int32_t exitCode)
{
	::PostQuitMessage(exitCode);
}

void WindowsApplication::ShowCursor(bool enableShow)
{
	::ShowCursor(enableShow ? TRUE : FALSE);
}

void WindowsApplication::EnableFloatingException(unsigned int stat)
{
	unsigned int currStat;
	_controlfp_s(&currStat, 0, 0);

	unsigned int newStat = currStat;
	newStat &= ~stat;
	_controlfp_s(&currStat, newStat, MCW_EM);
}

} /* namespace tgon */
