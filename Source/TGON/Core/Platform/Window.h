/**
 * @filename    Window.h
 * @author      ggomdyu
 * @since       02/15/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"
#include "Core/Math/Point.h"
#include "Core/Math/Extent.h"
#include "Core/Object/Delegate.h"

namespace tgon
{

class WindowImpl;
struct WindowStyle;

class TGON_API Window final :
    private std::enable_shared_from_this<Window>,
    private boost::noncopyable
{
/* @section Private constructor */
private:
    Window();
    Window(const WindowStyle& windowStyle);

/* @section Public constructor */
public:
    ~Window();
    
/* @section Public method */
public:
    static std::shared_ptr<Window> Create();
    static std::shared_ptr<Window> Create(const WindowStyle& windowStyle);
    void Show();
    void Hide();
    void Close();
    void Maximize();
    void Minimize();
    void BringToFront();
    void SetPosition(int32_t x, int32_t y);
    void SetSize(int32_t width, int32_t height);
    void SetTitle(const char* title);
    void SetTopMost(bool setTopMost);
    void SetTransparency(float transparency);
    void GetPosition(int32_t* x, int32_t* y) const;
    void GetSize(int32_t* width, int32_t* height) const;
    void GetTitle(char* destStr) const;
    I32Point GetPosition() const;
    I32Extent2D GetSize() const;
    float GetTransparency() const;
    void* GetNativeWindow();
    const void* GetNativeWindow() const;
    bool HasCaption() const;
    bool IsResizable() const;
    bool IsMaximized() const;
    bool IsMinimized() const;
    bool IsTopMost() const;

/* @section Public event handler */
public:
    Delegate<void(int32_t x, int32_t)> OnWindowMove;
    Delegate<void(int32_t, int32_t)> OnWindowResize;
    Delegate<void()> OnWindowMaximize;
    Delegate<void()> OnWindowMinimize;
    Delegate<void()> OnWindowEnterFullScreen;
    Delegate<void()> OnWindowExitFullScreen;
    Delegate<void()> OnWindowWillClose;
    Delegate<void()> OnWindowDidClose;
    Delegate<void()> OnWindowGetFocus;
    Delegate<void()> OnWindowLoseFocus;

/* @section Private variable */
private:
    std::unique_ptr<WindowImpl> m_impl;
};

} /* namespace tgon */
