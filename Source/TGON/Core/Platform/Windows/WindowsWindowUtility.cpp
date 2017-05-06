#include "PrecompiledHeader.h"
#include "WindowsWindowUtility.h"

#include <codecvt>
#include <cassert>
#include "WindowsWindow.h"

#include "Core/String/TEncoding.h"

namespace tgon {
namespace platform {
    
void ConvertWindowStyleToDword(const WindowStyle& wndStyle, DWORD* exWndStyle, DWORD* normalWndStyle)
{
	*exWndStyle = 0;
	*normalWndStyle = 0;

	/* Extended style */
    if (wndStyle.topMost)
    {
		*exWndStyle |= WS_EX_TOPMOST;
	}

    if (wndStyle.supportPerPixelTransparency)
    {
		*exWndStyle |= WS_EX_LAYERED;
	}

	/* Normal style */
    if (wndStyle.maximized)
    {
		*normalWndStyle |= WS_MAXIMIZE;
        assert(!wndStyle.minimized && "Can't be selected both Maximized and Minimized.");
    }
    else if (wndStyle.minimized)
    {
		*normalWndStyle |= WS_MINIMIZE;
	}

    if (wndStyle.resizeable)
    {
		*normalWndStyle |= WS_THICKFRAME;
        assert(!wndStyle.popup && "Can't be selected both Resizeable and Popup.");
    }
    else if (wndStyle.popup)
    {
		*normalWndStyle |= WS_POPUP;
	}

    if (wndStyle.showImmediately)
    {
		*normalWndStyle |= WS_VISIBLE;
	}
    if (wndStyle.supportWindowTransparency)
    {
		*normalWndStyle |= WS_EX_LAYERED;
	}
}

HWND CreateWindowForm(const WindowStyle& wndStyle, const wchar_t* className, HINSTANCE instanceHandle, void* extraParam)
{
	// Converts WindowStyle to platform dependent style.
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

bool HasSystemMenu(const WindowsWindow& window)
{
    DWORD dwStyle = ::GetWindowLongPtrW(window.GetWindowHandle(), GWL_STYLE);
    return (dwStyle & WS_CAPTION) != 0 && (dwStyle & WS_SYSMENU) != 0;
}

} /* namespace platform */
} /* namespace tgon */