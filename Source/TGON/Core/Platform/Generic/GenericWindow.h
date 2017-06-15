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
#include "Core/Platform/Config.h"

namespace tgon
{
namespace platform
{

class TGON_API GenericWindow
{
/**
 * @section Ctor/Dtor
 */
public:
    GenericWindow();
    virtual ~GenericWindow();
    
/**
 * @section Public method
 */
public:
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Quit() = 0;

    virtual void SetPosition(int32_t x, int32_t y) = 0;
    virtual void SetExtent(int32_t width, int32_t height) = 0;
    virtual void SetCaption(const char* caption) = 0;

    virtual void GetPosition(int32_t* x, int32_t* y) const = 0;
    virtual void GetExtent(int32_t* width, int32_t* height) const = 0;
    virtual void GetCaptionText(char* caption) const = 0;
    virtual bool HasCaption() const = 0;
    virtual bool IsResizable() const = 0;
    virtual bool IsHidden() const = 0;
    bool IsClosed() const noexcept;

/** 
 * @section Protected variable
 */ 
protected:
    bool m_isClosed;
};

} /* namespace platform */
} /* namespace tgon */
