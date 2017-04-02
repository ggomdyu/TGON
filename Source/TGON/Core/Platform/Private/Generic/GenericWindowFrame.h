/**
 * filename GenericWindowFrame.h
 * author   ggomdyu
 * since    01/09/2016
 */

#pragma once
#include "../../TConfig.h"

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>
#include <cstdint>

namespace tgon
{

enum class MouseType
{
	Left,
	Middle,
	Right,
};

struct WindowStyle
{
/**
 * @section Public variables
 */
public:
    /* @brief   The caption text of window */
	std::string title = "Hello World!";

    /* @brief   The transform of window */
	int32_t x = 100;
	int32_t y = 100;
	int32_t width = 500;
	int32_t height = 500;

	bool popup = false;                         /* If true, then do not make window frame. */
	bool fullScreen = false;                    /* If true, then show window as full screen when it was created. */
	bool supportWindowTransparency = false;     /* If true, then enable window surface's transparency. */
	bool supportPerPixelTransparency = false;   /* If true, then enable the window surface's perpixel transparency. */
	bool showTopOnCreated = false;              /* TODO: Not implemented / add comment */ 
	bool resizeable = true;                     /* If true, then make resizable frame to window. */

    /**
     * @brief   If true, the window is always showing on the top.
     * @warn    This can cause race each other top-most window.
     */
    bool topMost = false;

    /* @brief   If true, shows window maximized when it was created. */
    bool maximized = false;

    /* @brief   If true, then set window minimized when it was created. */
	bool minimized = false;
	
    /* @brief   If true, sets the position of the window to the center of screen when it was created. */
    bool showMiddle = true;
	
    /* @brief   If true, shows window immediately when it was created, else */
    bool showImmediately = true;
};

template <typename DerivedTy>
class TGON_API GenericWindowFrame :
	private boost::noncopyable
{
/**
 * @section Ctor/Dtor
 */
public:
	GenericWindowFrame( );
	virtual ~GenericWindowFrame( ) = 0;

/**
 * @section Event handlers
 */
public:
    virtual void OnMove(int32_t x, int32_t y) {}
    virtual void OnResize(int32_t width, int32_t height) {}
    virtual void OnMouseMove(int32_t x, int32_t y) {}
    virtual void OnMouseDown(int32_t x, int32_t y, MouseType mouseType) {}
    virtual void OnMouseUp(int32_t x, int32_t y, MouseType mouseType) {}
    virtual void OnMouseDoubleClick(int32_t x, int32_t y, MouseType mouseType) {}
    virtual void OnRawMouseMove(int32_t x, int32_t y) {}
    virtual void OnRawMouseDown(int32_t x, int32_t y, MouseType mouseType) {}
    virtual void OnRawMouseUp(int32_t x, int32_t y, MouseType mouseType) {}
    virtual bool OnGetFocus() { return true; }
    virtual bool OnLoseFocus() { return true; }

	/**
	 * @note	Called when window has begun closing.
	 * @return	True if you want to keep close.
	 */
    virtual bool OnDestroy() { return true; }

/**
 * @section Get methods
 */
public:
    bool IsClosed() const;

/**
 * @section Private variables
 */
protected:
	bool m_closed;
};

template<typename DerivedTy>
inline GenericWindowFrame<DerivedTy>::GenericWindowFrame() :
    m_closed(false)
{
}

template<typename DerivedTy>
inline GenericWindowFrame<DerivedTy>::~GenericWindowFrame()
{
    m_closed = true;
}

template<typename DerivedTy>
bool GenericWindowFrame<DerivedTy>::IsClosed() const
{
    return m_closed;
}

} /*namespace tgon*/