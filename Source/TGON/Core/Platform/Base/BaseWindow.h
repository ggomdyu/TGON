/**
 * @filename    BaseWindow.h
 * @author      ggomdyu
 * @since       01/09/2016
 * @brief       Set of Platform-agnostic Window interface.
 */

#pragma once
#include <string>
#include <cstdint>
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"

#include "BaseWindowType.h"

namespace tgon
{
namespace platform
{

class TGON_API BaseWindow
{
/* @section Public constructor */
public:
    BaseWindow();
    BaseWindow(const BaseWindow&) = delete;

/* @section Protected destructor */
public:
    virtual ~BaseWindow();

/* @section Public operator */
public:
    BaseWindow& operator=(const BaseWindow&) = delete;

/* @section Public method */
public:
    virtual void Quit() {}
    virtual void Maximize() {}
    virtual void Minimize() {}
    virtual void BringToFront() {}

    virtual void SetPosition(int32_t x, int32_t y) {}
    virtual void SetSize(int32_t width, int32_t height) {}
    virtual void SetTitle(const char* title) {}
    virtual void SetFullScreen(bool isFullScreen) {}
    virtual void GetPosition(int32_t* x, int32_t* y) const {}
    virtual void GetSize(int32_t* width, int32_t* height) const {}
    virtual void GetCaptionTitle(char* destCaptionTitle) const {}
    virtual bool HasCaption() const;
    virtual bool IsResizable() const;
    virtual bool IsMaximized() const;
    virtual bool IsMinimized() const;
    virtual bool IsClosed() const noexcept;

    virtual void OnMove(int32_t x, int32_t y) {}
    virtual void OnResize(int32_t width, int32_t height) {}
    virtual void OnMaximize() {}
    virtual void OnMinimize() {}
    virtual void OnEnterFullScreen() {}
    virtual void OnExitFullScreen() {}

/* @section Protected variable */
private:
    bool m_isClosed;
};

} /* namespace platform */
} /* namespace tgon */
