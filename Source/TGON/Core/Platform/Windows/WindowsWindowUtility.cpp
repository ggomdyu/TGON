#include "PrecompiledHeader.h"
#include "WindowsWindowUtility.h"

#include <cassert>

#include "WindowsWindow.h"
#include "Core/String/TEncoding.h"

namespace tgon
{
namespace platform
{
namespace windows
{
    
void ConvertWindowStyleToDword(const TWindowStyle& wndStyle, DWORD* extendedStyle, DWORD* normalStyle)
{
	*extendedStyle = 0;
	*normalStyle = 0;

	/* Normal style */
    *normalStyle |= WS_VISIBLE;
    
    if (wndStyle.maximized)
    {
		*normalStyle |= WS_MAXIMIZE;
        assert(!wndStyle.minimized && "Can't be selected both Maximized and Minimized.");
    }
    else if (wndStyle.minimized)
    {
		*normalStyle |= WS_MINIMIZE;
	}

    if (wndStyle.resizeable)
    {
		*normalStyle |= WS_THICKFRAME;
    }

    if (wndStyle.supportWindowTransparency)
    {
		*normalStyle |= WS_EX_LAYERED;
	}

    /* Extended style */
    if (wndStyle.topMost)
    {
        *extendedStyle |= WS_EX_TOPMOST;
    }

    if (wndStyle.supportPerPixelTransparency)
    {
        *extendedStyle |= WS_EX_LAYERED;
    }
}

HWND CreateWindowForm(const TWindowStyle& wndStyle, const wchar_t* className, HINSTANCE instanceHandle, void* extraParam)
{
	// Converts TWindowStyle to platform dependent style.
	DWORD exStyle, normalStyle;
    ConvertWindowStyleToDword(wndStyle, &exStyle, &normalStyle);

    wchar_t utf16Title[256] {};
    bool succeedToConvert = string::ConvertUTF8ToUTF16(wndStyle.caption.c_str(), reinterpret_cast<char*>(utf16Title)) != -1;
    if (!succeedToConvert)
    {
        return nullptr;
    }

	HWND wndHandle = CreateWindowExW(
		exStyle,
		className,
		utf16Title,
		normalStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // WS_CLIPSIBLINGS, WS_CLIPCHILDREN prevent other windows from drawing over or into our window.
        wndStyle.x,
        wndStyle.y,
		wndStyle.width, 
		wndStyle.height,
		nullptr,
		nullptr,
		instanceHandle,
		extraParam	// Extra parameter (pass this pointer when need to handling WM_CREATE)
	);

    if (wndHandle != nullptr)
    {
        ::SetForegroundWindow(wndHandle);
        ::SetFocus(wndHandle);
    }

	return wndHandle;
}

void ReshapeWindowForm(const WindowsWindow& from, const WindowsWindow& to)
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