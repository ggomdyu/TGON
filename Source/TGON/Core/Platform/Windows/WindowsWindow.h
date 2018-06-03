/**
 * @filename    WindowsWindow.h
 * @author      ggomdyu
 * @since       01/09/2016
 * @brief       The platform specific window class implementation.
 */

#pragma once
#include "../Generic/GenericWindow.h"

#include "WindowsWindowFwd.h"

namespace tgon
{

class TGON_API WindowsWindow :
    public GenericWindow
{
public:
    TGON_RUNTIME_OBJECT(WindowsWindow)

/* @section Public constructor */
public:
    WindowsWindow() = default;
    explicit WindowsWindow(const WindowStyle& windowStyle);
    WindowsWindow(WindowsWindow&& rhs) noexcept;

/* @section Public operator */
protected:
    WindowsWindow& operator=(WindowsWindow&& rhs) noexcept;

/* @section Public destructor */
public:
    virtual ~WindowsWindow() override;

/* @section Public method */
public:
    virtual void Show() final override;
    virtual void Hide() final override;
    virtual void Close() final override;
    virtual void Maximize() final override;
    virtual void Minimize() final override;
    virtual void BringToFront() final override;
    void Flash();
    virtual void SetPosition(int32_t x, int32_t y) final override;
    virtual void SetSize(int32_t width, int32_t height) final override;
    virtual void SetTitle(const char* title) final override;
    virtual void SetTopMost(bool setTopMost) final override;
    virtual void SetTransparency(float transparency) final override;
    virtual void GetPosition(int32_t* x, int32_t* y) const final override;
    virtual void GetSize(int32_t* width, int32_t* height) const final override;
    virtual void GetTitle(char* destStr) const final override;
    virtual float GetTransparency() const final override;
    virtual const void* GetNativeWindow() const final override;
    virtual bool HasCaption() const final override;
    virtual bool IsResizable() const final override;
    virtual bool IsMaximized() const final override;
    virtual bool IsMinimized() const final override;
    virtual bool IsTopMost() const final override;

    LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam);
    
    using SuperType::GetPosition;
    using SuperType::GetSize;
    using SuperType::GetNativeWindow;

/* @section Private method */
private:
    void SetUserData(void* data);

/* @section Protected variable */
protected:
    HWND m_wndHandle;
    bool m_isDwmCompositionEnabled;
};

} /* namespace tgon */