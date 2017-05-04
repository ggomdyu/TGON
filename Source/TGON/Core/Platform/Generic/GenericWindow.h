/**
 * @filename    GenericWindow.h
 * @author   ggomdyu
 * since    01/09/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <string>
#include <cstdint>

#include "Core/Platform/TConfig.h"
#include "Core/Math/TPoint.h"
#include "Core/Math/TExtent.h"
#include "Core/Math/TRect.h"

namespace tgon {
namespace window {

enum class MouseType
{
	Left,
	Middle,
	Right,
};

struct WindowStyle
{
/**
 * @section Public variable
 */
public:
	std::string caption = u8"Hello World!";

	std::size_t x = 100;
	std::size_t y = 100;
	std::size_t width = 500;
	std::size_t height = 500;

	bool popup = false;
	bool fullScreen = false;
	bool supportWindowTransparency = false;
	bool supportPerPixelTransparency = false;
	bool resizeable = true;
    bool topMost = false;
    bool maximized = false;
	bool minimized = false;
    bool showMiddle = true;
    bool showImmediately = true;
};

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
    virtual void OnResizeExtent(const math::TIntExtent& extent) {}
    virtual void OnMouseMove(const math::TIntPoint& position) {}
    virtual void OnMouseDown(const math::TIntPoint& position, MouseType mouseType) {}
    virtual void OnMouseUp(const math::TIntPoint& position, MouseType mouseType) {}
    virtual void OnMouseDoubleClick(const math::TIntPoint& position, MouseType mouseType) {}
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
    virtual void SetExtent(const math::TIntExtent& extent) = 0;
    virtual void SetCaption(const char* caption) = 0;

/** 
 * @section Get method
 */ 
public:
    virtual const math::TIntPoint GetPosition() const = 0;
    virtual const math::TIntExtent GetExtent() const = 0;
    virtual void GetCaptionText(char* caption) const = 0;

    bool IsClosed() const noexcept;

/** 
 * @section Protected variable
 */ 
protected:
    bool m_isClosed;
};

} /* namespace window */
} /* namespace tgon */