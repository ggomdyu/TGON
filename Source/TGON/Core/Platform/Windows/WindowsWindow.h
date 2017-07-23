/**
 * @filename    WindowsWindow.h
 * @author      ggomdyu
 * @since       11/12/2015
 */

#pragma once
#include "../Generic/GenericWindow.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>

namespace tgon
{
namespace platform
{
namespace windows
{
    
class TGON_API WindowsWindow :
    public GenericWindow
{
/** 
 * @section Ctor/Dtor
 */ 
public:
	explicit WindowsWindow(const TWindowStyle& wndStyle, HINSTANCE instanceHandle);
	virtual ~WindowsWindow();

public:
    bool PumpEvent();
    virtual void Show() override;
    virtual void Hide() override;
    virtual void Quit() override;
    virtual void Maximize() override;
    virtual void Minimize() override;
    virtual void BringToFront() override;
    void Flash();

public:
    virtual void SetPosition(int32_t x, int32_t y) override;
    virtual void SetExtent(int32_t width, int32_t height) override;
    virtual void SetCaption(/*IN*/ const char* caption) override;
    void SetTopMost(bool setTopMost);
    void SetTransparent(float opacity);
    void SetPerPixelTransparent(float opacity);
    void SetColorMask(/*maskColor*/);

public:
    virtual void GetPosition(/*OUT*/ int32_t* x, /*OUT*/ int32_t* y) const override;
    virtual void GetExtent(/*OUT*/ int32_t* width, /*OUT*/ int32_t* height) const override;
    virtual void GetCaptionText(/*OUT*/ char* caption) const override;
    virtual bool HasCaption() const override;
    //bool GetTransparent() const;
    //bool GetPerPixelTransparent() const;
    virtual bool IsResizable() const override;
    virtual bool IsMaximized() const override;
    virtual bool IsMinimized() const override;
    virtual bool IsTopMost() const override;
    HWND GetWindowHandle() const noexcept;

private:
	HWND m_wndHandle;
};

} /* namespace windows */

using TWindow = windows::WindowsWindow;

} /* namespace platform */
} /* namespace tgon */