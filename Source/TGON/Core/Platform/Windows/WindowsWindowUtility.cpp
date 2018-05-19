#include "PrecompiledHeader.h"

#include <cassert>

#include "Core/Debug/Log.h"
#include "Core/Platform/Generic/GenericWindowType.h"
#include "Core/String/Encoding.h"

#include "WindowsWindowUtility.h"

namespace tgon
{

void ConverWindowStyleToNative(const WindowStyle& windowStyle, DWORD* normalStyle, DWORD* extendedStyle)
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

HWND CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className, void* extraParam)
{
	// Convert WindowStyle to native window style.
	DWORD normalStyle, extendedStyle;
    ConverWindowStyleToNative(windowStyle, &normalStyle, &extendedStyle);

    wchar_t utf16Title[512] {};
    bool succeeded = UTF8::Convert<UTF16LE>(windowStyle.title.c_str(), windowStyle.title.length(), reinterpret_cast<char*>(utf16Title), 512) != -1;
    if (succeeded == false)
    {
        return nullptr;
    }

    POINT windowPos {windowStyle.x, windowStyle.y};
    if (windowStyle.showMiddle)
    {
        // Set window position to middle of screen.
        windowPos.x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (windowStyle.width / 2);
        windowPos.y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (windowStyle.height / 2);
    }

	HWND wndHandle = CreateWindowExW(
		extendedStyle,
		className,
        utf16Title,
		normalStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // WS_CLIPSIBLINGS, WS_CLIPCHILDREN prevent other windows from drawing over or into our window.
        windowPos.x,
        windowPos.y,
		windowStyle.width,
		windowStyle.height,
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