#include "PrecompiledHeader.pch"
#include "WindowsWindow.h"

#include <cassert>

#include "Core/String/TEncoding.h"

#include "WindowsWindowUtility.h"

namespace tgon
{
namespace platform
{
namespace windows
{
    
void ConvertToNativeWindowStyle(const WindowStyle& windowStyle, DWORD* extendedStyle, DWORD* normalStyle)
{
	*extendedStyle = 0;
	*normalStyle = 0;

	/* Normal style */
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

    if (windowStyle.supportWindowTransparency)
    {
		*normalStyle |= WS_EX_LAYERED;
	}

    /* Extended style */
    if (windowStyle.topMost)
    {
        *extendedStyle |= WS_EX_TOPMOST;
    }

    if (windowStyle.supportPerPixelTransparency)
    {
        *extendedStyle |= WS_EX_LAYERED;
    }
}

HWND CreateNativeWindow(const WindowStyle& windowStyle, HINSTANCE instanceHandle, const wchar_t* className, void* extraParam)
{
	// Converts WindowStyle to platform dependent style.
	DWORD exStyle, normalStyle;
    ConvertToNativeWindowStyle(windowStyle, &exStyle, &normalStyle);

    wchar_t utf16Title[256] {};
    bool succeedToConvert = string::ConvertUTF8ToUTF16(windowStyle.caption.c_str(), reinterpret_cast<char*>(utf16Title)) != -1;
    if (!succeedToConvert)
    {
        return nullptr;
    }

	HWND wndHandle = CreateWindowExW(
		exStyle,
		className,
		utf16Title,
		normalStyle /*| WS_CLIPSIBLINGS | WS_CLIPCHILDREN*/, // WS_CLIPSIBLINGS, WS_CLIPCHILDREN prevent other windows from drawing over or into our window.
        windowStyle.x,
        windowStyle.y,
		windowStyle.width, 
		windowStyle.height,
		nullptr,
		nullptr,
		instanceHandle,
		extraParam	// Extra parameter (pass this pointer when need to handling WM_CREATE)
	);

    if (wndHandle != nullptr)
    {
        //::SetForegroundWindow(wndHandle);
        //::SetFocus(wndHandle);
    }

	return wndHandle;
}

void CopyAndPasteWindowShape(const WindowsWindow& from, const WindowsWindow& to)
{
    // Change placement of the Window.
    {
	    ::WINDOWPLACEMENT wndPlacementInfo;
        ::GetWindowPlacement(to.GetWindowHandle(), &wndPlacementInfo);
        
        ::SetWindowPlacement(from.GetWindowHandle(), &wndPlacementInfo);
    }
        
    // Change Style attribute of the Window.
    {
        DWORD style = GetWindowLongPtrW(to.GetWindowHandle(), GWL_STYLE);
        ::SetWindowLongPtrW(from.GetWindowHandle(), GWL_STYLE, style);

        DWORD extendedStyle = GetWindowLongPtrW(to.GetWindowHandle(), GWL_EXSTYLE);
        SetWindowLongPtrW(from.GetWindowHandle(), GWL_EXSTYLE, extendedStyle);

        // Let changes be affected.
        ::SetWindowPos(from.GetWindowHandle(), nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}

} /* namespace windows */
} /* namespace platform */
} /* namespace tgon */