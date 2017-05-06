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

class TGON_API WindowsWindow :
    public GenericWindow
{
/** 
 * @section Ctor/Dtor
 */ 
public:
	explicit WindowsWindow(const WindowStyle& wndStyle);
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
    virtual void SetExtent(const math::TIntExtent& extent) override;
    virtual void SetCaption(const char* caption) override;
    void SetTopMost(bool setTopMost);
    void SetTransparent(float);
    void SetPerPixelTransparent(float);

/** 
 * @section Get method
 */ 
public:
    virtual const math::TIntPoint GetPosition() const override;
    virtual const math::TIntExtent GetExtent() const override;
    virtual void GetCaptionText(char* caption) const override;
    bool IsTopMost() const;
    //bool GetTransparent() const;
    //bool GetPerPixelTransparent() const;
    HWND GetWindowHandle() const noexcept;
    bool HasThickframe() const;

/** 
 * @section Private variable
 */ 
private:
	HWND m_wndHandle;
};

using TWindow = WindowsWindow;

} /* namespace platform */
} /* namespace tgon */