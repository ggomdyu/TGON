#include "PrecompiledHeader.pch"

#include "WindowsWindowUtility.h"

#include "Core/Platform/WindowType.h"
#include "Core/String/Encoding.h"

#include <cassert>

namespace tgon
{
namespace platform
{

void ConverWindowStyleToNative(const WindowStyle& windowStyle, DWORD* extendedStyle, DWORD* normalStyle)
{
	*extendedStyle = 0;
	*normalStyle = 0;

	// Set Normal style
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

        if (windowStyle.enableSystemButton)
        {
            *normalStyle |= WS_SYSMENU;
            *normalStyle |= WS_MINIMIZEBOX;
            *normalStyle |= WS_MAXIMIZEBOX;
        }
    }

    // Set Extended style
    {
        if (windowStyle.topMost)
        {
            *extendedStyle |= WS_EX_TOPMOST;
        }

        if (windowStyle.supportPerPixelTransparency)
        {
            *extendedStyle |= WS_EX_LAYERED;
        }

        if (windowStyle.supportWindowTransparency)
        {
            *extendedStyle |= WS_EX_LAYERED;
        }
    }
}

HWND CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className, void* extraParam)
{
	// Converts WindowStyle to platform dependent style.
	DWORD exStyle, normalStyle;
    ConverWindowStyleToNative(windowStyle, &exStyle, &normalStyle);

    wchar_t utf16Title[256] {};
    bool succeedToConvert = string::ConvertUTF8ToUTF16(windowStyle.title.c_str(), reinterpret_cast<char*>(utf16Title)) != -1;
    if (!succeedToConvert)
    {
        return nullptr;
    }

    // Set window position to middle of screen if required.
    int newWindowX = windowStyle.x;
    int newWindowY = windowStyle.y;
    if (windowStyle.showMiddle)
    {
        newWindowX = (GetSystemMetrics(SM_CXSCREEN) / 2) - (windowStyle.width / 2);
        newWindowY = (GetSystemMetrics(SM_CYSCREEN) / 2) - (windowStyle.height / 2);
    }

	HWND wndHandle = CreateWindowExW(
		exStyle,
		className,
		utf16Title,
		normalStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // WS_CLIPSIBLINGS, WS_CLIPCHILDREN prevent other windows from drawing over or into our window.
        newWindowX,
        newWindowY,
		windowStyle.width,
		windowStyle.height,
		nullptr,
		nullptr,
		instanceHandle,
		extraParam
	);

	return wndHandle;
}

} /* namespace platform */
} /* namespace tgon */