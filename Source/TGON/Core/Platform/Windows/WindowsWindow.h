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

#include "Core/Platform/Base/BaseWindow.h"

namespace tgon
{
namespace platform
{
namespace windows
{
    
class TGON_API WindowsWindow :
    public BaseWindow
{
/* @section Public constructor */
public:
	explicit WindowsWindow(const WindowStyle& wndStyle);

/* @section Public destructor */
public:
	virtual ~WindowsWindow();

/* @section Public method */
public:
    virtual void Show() override;
    virtual void Hide() override;
    virtual void Close() override;
    virtual void Maximize() override;
    virtual void Minimize() override;
    virtual void BringToFront() override;
    bool PumpMessage(MSG* message);
    void Flash();

    virtual void SetPosition(int32_t x, int32_t y) override;
    virtual void SetSize(int32_t width, int32_t height) override;
    virtual void SetTitle(const char* title) override;
    void SetTopMost(bool setTopMost);
    void SetTransparent(float opacity);
    void SetPerPixelTransparent(float opacity);
    //void SetColorMask(/*maskColor*/);
    virtual void GetPosition(int32_t* x, int32_t* y) const override;
    virtual void GetSize(int32_t* width, int32_t* height) const override;
    virtual void GetTitle(char* destTitleStr) const override;
    virtual void* GetNativeWindow() noexcept override;
    virtual bool HasCaption() const override;
    virtual bool IsMaximized() const override;
    virtual bool IsTopMost() const;
    virtual bool IsClosed() const noexcept override;
    virtual bool IsResizable() const override;
    //bool GetTransparent() const;
    //bool GetPerPixelTransparent() const;

	LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam); 

/* @section Private variable */
private:
	HWND m_wndHandle;
};

} /* namespace windows */

using Window = windows::WindowsWindow;

} /* namespace platform */
} /* namespace tgon */
