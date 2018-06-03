/**
 * @filename    MacOSWindow.h
 * @author      ggomdyu
 * @since       07/16/2017
 * @brief       The platform specific window class implementation.
 */

#pragma once
#import "../Generic/GenericWindow.h"

#import "MacOSWindowFwd.h"

namespace tgon
{

class TGON_API MacOSWindow :
    public GenericWindow
{
public:
    TGON_RUNTIME_OBJECT(MacOSWindow)

/* @section Public constructor */
public:
    MacOSWindow() = default;
    explicit MacOSWindow(const WindowStyle& windowStyle);
    MacOSWindow(MacOSWindow&& rhs) noexcept;

/* @section Public operator */
public:
    MacOSWindow& operator=(MacOSWindow&& rhs) noexcept;

/* @section Public destructor */
public:
    virtual ~MacOSWindow() override;

/* @section Public method */
public:
    virtual void Show() final override;
    virtual void Hide() final override;
    virtual void Close() final override;
    virtual void Maximize() final override;
    virtual void Minimize() final override;
    virtual void SetPosition(int32_t x, int32_t y) final override;
    virtual void SetSize(int32_t width, int32_t height) final override;
    virtual void SetTitle(const char* title) final override;
    virtual void SetFullScreen(bool isFullScreen) final override;
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
    using GenericWindow::GetPosition;
    using GenericWindow::GetSize;
    using GenericWindow::GetNativeWindow;

/* @section Protected variable */
protected:
    NSWindow* m_nsWindow;
    WindowDelegate* m_windowDelegate;
};

} /* namespace tgon */
