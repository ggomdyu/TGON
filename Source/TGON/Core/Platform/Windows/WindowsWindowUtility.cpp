#include "PrecompiledHeader.h"

#include "Core/Debug/Log.h"
#include "Core/Debug/LogType.h"
#include "Core/String/Encoding.h"
#include "Core/Math/Point.h"
#include "Core/Math/Extent.h"

#include "../WindowType.h"

#include "WindowsWindowUtility.h"

namespace tgon
{

void WindowsWindowUtility::ConverWindowStyleToNative(const WindowStyle& windowStyle, DWORD* normalStyle, DWORD* extendedStyle)
{
	*extendedStyle = 0;
	*normalStyle = 0;

	// Assemble normal window style
    {
        *normalStyle |= WS_VISIBLE;
        
        if (windowStyle.maximized)
        {
	    	*normalStyle |= WS_MAXIMIZE;
            assert(!windowStyle.minimized && "Can't be selected both Maximized and Minimized.");
        }
        else if (windowStyle.minimized)
        {
	    	*normalStyle |= WS_MINIMIZE;
	    }

        if (windowStyle.resizeable)
        {
	    	*normalStyle |= WS_THICKFRAME;
        }

        if (!windowStyle.hasCaption)
        {
            *normalStyle |= WS_POPUP;
        }
        else
        {
            *normalStyle |= WS_OVERLAPPED;
            *normalStyle |= WS_CAPTION;
            *normalStyle |= WS_THICKFRAME;
        }

        if (windowStyle.enableSystemButton)
        {
            *normalStyle |= WS_SYSMENU;
            *normalStyle |= WS_MINIMIZEBOX;
            *normalStyle |= WS_MAXIMIZEBOX;
        }
    }

    // Assemble extended window style
    {
        if (windowStyle.topMost)
        {
            *extendedStyle |= WS_EX_TOPMOST;
        }

        if (windowStyle.supportPerPixelTransparency)
        {
            *extendedStyle |= WS_EX_LAYERED;
        }

        if (windowStyle.supportTransparency)
        {
            *extendedStyle |= WS_EX_LAYERED;
        }
    }
}

HWND WindowsWindowUtility::CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className, void* extraParam)
{
	// Convert WindowStyle to native window style.
	DWORD normalStyle, extendedStyle;
    ConverWindowStyleToNative(windowStyle, &normalStyle, &extendedStyle);

    wchar_t utf16Title[512] {};
    bool isConverSucceeded = UTF8::Convert<UTF16LE>(windowStyle.title.c_str(), windowStyle.title.length(), utf16Title, std::extent_v<decltype(utf16Title)>);
    if (isConverSucceeded == false)
    {
        return nullptr;
    }

    I32Point windowPos {windowStyle.x, windowStyle.y};
    if (windowStyle.showMiddle)
    {
        // Set window position to middle of screen.
        windowPos.x = (GetSystemMetrics(SM_CXSCREEN) * 0.5f) - (windowStyle.width * 0.5f);
        windowPos.y = (GetSystemMetrics(SM_CYSCREEN) * 0.5f) - (windowStyle.height * 0.5f);
    }

    // Convert the client size to window size.
    RECT windowSize = {0, 0, windowStyle.width, windowStyle.height};
    AdjustWindowRect(&windowSize, normalStyle, FALSE);
 
	HWND wndHandle = CreateWindowExW(
		extendedStyle,
		className,
        utf16Title,
        normalStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
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