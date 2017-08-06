/**
 * @filename    BaseWindow.h
 * @author      ggomdyu
 * @since       01/09/2016
 * @desc        Set of Platform-agnostic Window interface.
 */

#pragma once
#include <string>
#include <cstdint>
#include <boost/noncopyable.hpp>

#include "BaseWindowType.h"

#include "Core/Platform/Config.h"

namespace tgon
{
namespace platform
{

class TGON_API BaseWindow
{
/* @section Ctor/Dtor */
public:
    BaseWindow();
    virtual ~BaseWindow();
    
/* @section Public method */
public:
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Quit() = 0;
	virtual void Maximize() = 0;
	virtual void Minimize() = 0;
	virtual void BringToFront() = 0;

    virtual void SetPosition(int32_t x, int32_t y) = 0;
    virtual void SetSize(int32_t width, int32_t height) = 0;
    virtual void SetCaptionTitle(const char* captionTitle) = 0;

    virtual void GetPosition(int32_t* x, int32_t* y) const = 0;
    virtual void GetSize(int32_t* width, int32_t* height) const = 0;
    virtual void GetCaptionTitle(char* destCaptionTitle) const = 0;
    virtual bool HasCaption() const = 0;
    virtual bool IsResizable() const = 0;
	virtual bool IsMaximized() const = 0;
	virtual bool IsMinimized() const = 0;
    bool IsClosed() const noexcept;

/* @section Protected variable */
protected:
    bool m_isClosed;
};

} /* namespace platform */
} /* namespace tgon */
