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
    public BaseWindow
{
/* @section Ctor/Dtor */
public:
	explicit WindowsWindow(const WindowStyle& wndStyle);
	~WindowsWindow();

/* @section Public method */
public:
    bool PumpEvent();
    virtual void Show() override;
    virtual void Hide() override;
    virtual void Quit() override;
    virtual void Maximize() override;
    virtual void Minimize() override;
    virtual void BringToFront() override;
    void Flash();

    virtual void SetPosition(int32_t x, int32_t y) override;
    virtual void SetSize(int32_t width, int32_t height) override;
    virtual void SetTitle(const char* captionTitle) override;
    void SetTopMost(bool setTopMost);
    void SetTransparent(float opacity);
    void SetPerPixelTransparent(float opacity);
    //void SetColorMask(/*maskColor*/);
    virtual void GetPosition(int32_t* x, int32_t* y) const override;
    virtual void GetSize(int32_t* width, int32_t* height) const override;
    virtual void GetCaptionTitle(char* destCaptionTitle) const override;
    virtual bool HasCaption() const override;
    //bool GetTransparent() const;
    //bool GetPerPixelTransparent() const;
    virtual bool IsResizable() const override;
    virtual bool IsMaximized() const override;
    virtual bool IsTopMost() const;
    virtual bool IsClosed() const noexcept override;
    HWND GetWindowHandle() const noexcept;

	LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam); 

private:
	HWND m_wndHandle;
};

} /* namespace windows */

using Window = windows::WindowsWindow;

} /* namespace platform */
} /* namespace tgon */
