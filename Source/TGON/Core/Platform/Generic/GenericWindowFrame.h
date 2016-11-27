/**
 * Author : Cha Junho
 * Date : 01/09/2016
 * Latest author : 
 * Latest date :
 */


#pragma once
#include "../OSAL/PlatformInclude.h"

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>
#include <cstdint>


namespace tgon
{

// TODO: Move to other header
enum class MouseType
{
	Left,
	Middle,
	Right,
};

struct WindowStyle
{
/**
 * Commands
 */ 
public:
	/**
	 * @param	xmlPath     Full path of XML
	 * @return              Window-style data parsed from xml
	 */
	static WindowStyle LoadFromXML( const char* xmlPath );
	
/**
 * Public variables
 */ 
public:
	std::string title = "Hello World!"; /* Caption text of window */
	int32_t x = 100; /* Window transform */
	int32_t y = 100; /* Window transform */
	int32_t width = 500; /* Window transform */
	int32_t height = 500; /* Window transform */

	bool popup = false; /* If true, then do not make window frame. */
	bool fullScreen = false; /* If true, then show window as full screen when it was created. */
	bool supportWindowTransparency = false; /* If true, then enable window surface's transparency. */
	bool supportPerPixelTransparency = false; /* If true, then enable the window surface's perpixel transparency. */
	bool showTopOnCreated = false; /* TODO: Not implemented / add comment */ 
	bool resizeable = true; /* If true, then make resizable frame to window. */
	bool topMost = false; /* Show window always top. This can cause race each other top-most window. */
	bool maximized = false; /* If true, then set window maximized when it was created. */
	bool minimized = false; /* If true, then set window minimized when it was created. */
	bool showMiddle = true; /* If true, then set window position to middle of screen when it was created. */
	bool showImmediately = true; /* If true, then show window immediately when it was created, else */
};

template <typename DerivedTy>
class TGON_API GenericWindowFrame :
	private boost::noncopyable
{
/**
 * Ctor/Dtor
 */
public:
	GenericWindowFrame( );
	virtual ~GenericWindowFrame( ) = 0;

/**
 * Event handlers
 */
public:
	virtual void OnMove( int32_t x, int32_t y ) {}
	virtual void OnResize( int32_t width, int32_t height ) {}
	virtual void OnMouseMove( int32_t x, int32_t y ) {}
	virtual void OnMouseDown( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual void OnMouseUp( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual void OnMouseDoubleClick( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual void OnRawMouseMove( int32_t x, int32_t y ) {}
	virtual void OnRawMouseDown( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual void OnRawMouseUp( int32_t x, int32_t y, MouseType mouseType ) {}
	virtual bool OnGetFocus( ) { return true; }
	virtual bool OnLoseFocus( ) { return true; }

	/**
	 * @note	Called when window has begun closing.
	 * @return	Return true if you want to keep close.
	 */
	virtual bool OnDestroy( ) { return true; }

/**
 * Gets
 */
public:
	bool IsClosed( ) const;

/**
 * Private variables
 */
protected:
	bool m_closed;
};


template<typename DerivedTy>
inline GenericWindowFrame<DerivedTy>::GenericWindowFrame( ) :
	m_closed( false )
{
}

template<typename DerivedTy>
inline GenericWindowFrame<DerivedTy>::~GenericWindowFrame( )
{
	m_closed = true;
}

template<typename DerivedTy>
bool GenericWindowFrame<DerivedTy>::IsClosed( ) const
{
	return m_closed;
}


} /*namespace tgon*/