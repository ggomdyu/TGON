/**
 * @filename    WindowsWindow.h
 * @author      ggomdyu
 * @since       11/12/2015
 */

#pragma once
#include <Windows.h>
#ifndef NOMINMAX
#	define NOMINMAX
#endif

#include "../Base/BaseWindow.h"

namespace tgon
{
namespace platform
{
namespace windows
{
    
class TGON_API WindowsWindow :
    public BaseWindow<WindowsWindow>
{
/* @section Ctor/Dtor */
public:
	explicit WindowsWindow(const WindowStyle& wndStyle);
	~WindowsWindow();

/* @section Public method */
public:
    bool PumpEvent();
    void Show();
    void Hide();
    void Quit();
    void Maximize();
    void Minimize();
    void BringToFront();
    void Flash();

    void SetPosition(int32_t x, int32_t y);
    void SetSize(int32_t width, int32_t height);
    void SetCaptionTitle(const char* captionTitle);
    void SetTopMost(bool setTopMost);
    void SetTransparent(float opacity);
    void SetPerPixelTransparent(float opacity);
    //void SetColorMask(/*maskColor*/);
    void GetPosition(int32_t* x, int32_t* y) const;
    void GetSize(int32_t* width, int32_t* height) const;
    void GetCaptionTitle(char* destCaptionTitle) const;
    bool HasCaption() const;
    //bool GetTransparent() const;
    //bool GetPerPixelTransparent() const;
    bool IsResizable() const;
    bool IsMaximized() const;
    bool IsHidden() const;
    bool IsTopMost() const;
    bool IsClosed() const noexcept;
    HWND GetWindowHandle() const noexcept;

	LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam); 
	void OnGetFocus() {}
	void OnLoseFocus() {}
	void OnMove(std::size_t x, std::size_t y) {}
	void OnResize(std::size_t width, std::size_t height) {}

private:
	HWND m_wndHandle;
};

} /* namespace windows */

using Window = windows::WindowsWindow;

} /* namespace platform */
} /* namespace tgon */
