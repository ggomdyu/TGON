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

namespace tgon {
namespace platform {
namespace windows {

class TGON_API WindowsWindow :
    public GenericWindow
{
/** 
 * @section Ctor/Dtor
 */ 
public:
	explicit WindowsWindow(const TWindowStyle& wndStyle);
	virtual ~WindowsWindow();

/** 
 * @section Public command method
 */ 
public:
    bool PumpEvent();
    virtual void Show() override;
    virtual void Hide() override;
    virtual void Quit() override;
    virtual void Maximize() override;
    virtual void Minimize() override;
    virtual void BringToFront() override;
    void Flash();

/**
 * @section Event handler
 */
public:
    LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam);

/**
 * @section Set method
 */
public:
    virtual void SetPosition(const math::TIntPoint& position) override;
    virtual void SetExtent(const math::TIntExtent2D& extent) override;
    virtual void SetCaption(const char* caption) override;
    void SetTopMost(bool setTopMost);
    void SetTransparent(float);
    void SetPerPixelTransparent(float);

/** 
 * @section Get method
 */ 
public:
    virtual const math::TIntPoint GetPosition() const override;
    virtual const math::TIntExtent2D GetExtent() const override;
    virtual void GetCaptionText(char* caption) const override;
    virtual bool HasCaption() const override;
    //bool GetTransparent() const;
    //bool GetPerPixelTransparent() const;
    virtual bool IsResizable() const override;
    virtual bool IsMaximized() const override;
    virtual bool IsMinimized() const override;
    virtual bool IsTopMost() const override;
    HWND GetWindowHandle() const noexcept;

/** 
 * @section Private variable
 */ 
private:
	HWND m_wndHandle;
};

} /* namespace windows */

using TWindow = windows::WindowsWindow;

} /* namespace platform */
} /* namespace tgon */