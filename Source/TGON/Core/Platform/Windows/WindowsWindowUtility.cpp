#include "PrecompiledHeader.h"

#include "Core/Debug/Log.h"
#include "Core/Debug/LogType.h"
#include "Core/String/Encoding.h"
#include "Core/Math/Point.h"
#include "Core/Math/Extent.h"

#include "WindowsWindowUtility.h"

namespace tgon
{

void WindowsWindowUtility::ConverWindowStyleToNative(const WindowStyle& windowStyle, DWORD* rawWindowStyle, DWORD* rawExtendedWindowStyle)
{
	*rawExtendedWindowStyle = 0;
	*rawWindowStyle = 0;

	// Create a normal window style.
    {
        *rawWindowStyle |= WS_VISIBLE;
        
        if (windowStyle.resizeable)
        {
	    	*rawWindowStyle |= WS_THICKFRAME;
        }

        if (!windowStyle.hasCaption)
        {
            *rawWindowStyle |= WS_POPUP;
        }
        else
        {
            *rawWindowStyle |= WS_OVERLAPPED;
            *rawWindowStyle |= WS_CAPTION;
            *rawWindowStyle |= WS_THICKFRAME;
        }

        if (windowStyle.enableSystemButton)
        {
            *rawWindowStyle |= WS_SYSMENU;
            *rawWindowStyle |= WS_MINIMIZEBOX;
            *rawWindowStyle |= WS_MAXIMIZEBOX;
        }
    }

    // Create a extended window style.
    {
        if (windowStyle.topMost)
        {
            *rawExtendedWindowStyle |= WS_EX_TOPMOST;
        }
    }
}

HWND WindowsWindowUtility::CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className, void* extraParam)
{
	// Convert the WindowStyle to the native window style.
	DWORD rawWindowStyle, rawExtendedWindowStyle;
    ConverWindowStyleToNative(windowStyle, &rawWindowStyle, &rawExtendedWindowStyle);

    wchar_t utf16Title[512] {};
    bool isConverSucceeded = UTF8::Convert<UTF16LE>(windowStyle.title.c_str(), windowStyle.title.length(), utf16Title, std::extent_v<decltype(utf16Title)>);
    if (isConverSucceeded == false)
    {
        return nullptr;
    }

    I32Point windowPos {windowStyle.x, windowStyle.y};
    if (windowStyle.showMiddle)
    {
        // Set the window position to middle of the screen.
        windowPos.x = (GetSystemMetrics(SM_CXSCREEN) * 0.5f) - (windowStyle.width * 0.5f);
        windowPos.y = (GetSystemMetrics(SM_CYSCREEN) * 0.5f) - (windowStyle.height * 0.5f);
    }

    // Convert the client size to window size.
    RECT windowSize = {0, 0, windowStyle.width, windowStyle.height};
    ::AdjustWindowRect(&windowSize, rawWindowStyle, FALSE);
 
	HWND wndHandle = ::CreateWindowExW(
		rawExtendedWindowStyle,
		className,
        utf16Title,
        rawWindowStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
        windowPos.x,
        windowPos.y,
        windowSize.right - windowSize.left,
        windowSize.bottom - windowSize.top,
		nullptr,
		nullptr,
		instanceHandle,
		extraParam
	);

    if (wndHandle == nullptr)
    {
        Log(LogLevel::Warning, "Failed to invoke CreateWindowExW. (Code: %d)", GetLastError());
    }

	return wndHandle;
}

} /* namespace tgon */