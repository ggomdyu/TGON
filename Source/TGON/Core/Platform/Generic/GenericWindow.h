/**
 * @filename    GenericWindow.h
 * @author      ggomdyu
 * @since       01/09/2016
 */

#pragma once
#include <string>
#include <cstdint>
#include <boost/noncopyable.hpp>

#include "GenericWindowType.h"
#include "Core/Platform/TConfig.h"

namespace tgon
{
namespace platform
{

class TGON_API GenericWindow
{
public:
    GenericWindow();
    virtual ~GenericWindow();
    
public:
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Quit() = 0;
    virtual void Maximize() = 0;
    virtual void Minimize() = 0;
    virtual void BringToFront() = 0;

public:
    virtual void SetPosition(int32_t x, int32_t y) = 0;
    virtual void SetExtent(int32_t width, int32_t height) = 0;
    virtual void SetCaption(/*IN*/ const char* caption) = 0;

public:
    virtual void GetPosition(/*OUT*/ int32_t* x, /*OUT*/ int32_t* y) const = 0;
    virtual void GetExtent(/*OUT*/ int32_t* width, /*OUT*/ int32_t* height) const = 0;
    virtual void GetCaptionText(/*OUT*/ char* caption) const = 0;
    virtual bool HasCaption() const = 0;
    virtual bool IsResizable() const = 0;
    virtual bool IsTopMost() const = 0;
    virtual bool IsMaximized() const = 0;
    virtual bool IsMinimized() const = 0;
    bool IsClosed() const noexcept;

/** 
 * @section Protected variable
 */ 
protected:
    bool m_isClosed;
};

} /* namespace platform */
} /* namespace tgon */