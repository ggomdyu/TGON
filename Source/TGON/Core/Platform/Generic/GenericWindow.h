/**
 * @filename    GenericWindow.h
 * @author      ggomdyu
 * @since       01/09/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <string>
#include <cstdint>

#include "GenericWindowType.h"

#include "Core/Platform/TConfig.h"
#include "Core/Math/TPoint.h"
#include "Core/Math/TExtent.h"
#include "Core/Math/TRect.h"

namespace tgon {
namespace platform {

class TGON_API GenericWindow
{
/**
 * @section Ctor/Dtor
 */
public:
    GenericWindow();
    virtual ~GenericWindow();

/**
 * @section Event handler
 */
public:
    virtual void OnMove(const math::TIntPoint& position) {}
    virtual void OnResizeExtent(const math::TIntExtent2D& extent) {}
    virtual void OnMouseMove(const math::TIntPoint& position) {}
    virtual void OnMouseDown(const math::TIntPoint& position, TMouseType mouseType) {}
    virtual void OnMouseUp(const math::TIntPoint& position, TMouseType mouseType) {}
    virtual void OnMouseDoubleClick(const math::TIntPoint& position, TMouseType mouseType) {}
    virtual void OnGetFocus() {}
    virtual void OnLoseFocus() {}
    virtual void OnDestroy() { m_isClosed = true; }

/** 
 * @section Public command method
 */ 
public:
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual void Quit() = 0;
    virtual void Maximize() = 0;
    virtual void Minimize() = 0;
    virtual void BringToFront() = 0;

/**
 * @section Set method
 */
public:
    virtual void SetPosition(const math::TIntPoint& position) = 0;
    virtual void SetExtent(const math::TIntExtent2D& extent) = 0;
    virtual void SetCaption(const char* caption) = 0;

/** 
 * @section Get method
 */ 
public:
    virtual const math::TIntPoint GetPosition() const = 0;
    virtual const math::TIntExtent2D GetExtent() const = 0;
    virtual void GetCaptionText(char* caption) const = 0;
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