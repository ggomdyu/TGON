/*
* Author : Cha Junho
* Date : 01/09/2016
* Latest author : 
* Latest date :
*/


#pragma once
#include "../PlatformInclude.h"

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

class WindowEventHandler
{
	//
	// Event handlers
	//
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

	/*
	 * @note	Called when window has begun closing.
	 * @return	Return true if you want to keep close.
	*/
	virtual bool OnDestroy( ) { return true; }

};

struct WindowStyle
{
	// 
	// Static variables
	// 
public:
	static const WindowStyle DefaultStyle;

	// 
	// Commands
	// 
public:
	/*
	 * @param	xmlPath	Full path of XML file
	 * @return	Return	WindowStyle which read from xml 
	*/
	static WindowStyle LoadFromXML( const char* xmlPath );

	//
	// Public variables
	//
public:
	/* @note	Set caption text of the window */
	std::string title = "TGON-Default";
	/* @note	Window transform */
	int32_t x = 100;
	int32_t y = 100;
	int32_t width = 500;
	int32_t height = 500;

	/* @note	If true, then do not make window frame. */
	bool popup = false;
	/* @note	If true, then show window as full-screen when it was created. */
	bool fullScreen = false;
	/* @note	If true, then enable window surface's transparency. */
	bool supportWindowTransparency = false;
	/* @note	If true, then enable the window surface's perpixel transparency. */
	bool supportPerPixelTransparency = false;
	/* @todo	Add comment */ 
	bool showTopOnCreated = false;
	/* @note	If true, then make resizable frame to window. */
	bool resizeable = true;
	
	/*
	 * @note	Show window always top.
	 * @warn	This can cause race each other top-most window.
	*/
	bool topMost = false;
	/* @note	If true, then set window maximized when it was created. */
	bool maximized = false;
	/* @note	If true, then set window minimized when it was created. */
	bool minimized = false;
	/* @note	If true, then set window position to middle of screen when it was created. */
	bool showMiddle = true;
	/* @note	If true, then show window immediately when it was created, else */
	bool showImmediately = true;
};

class TGON_API GenericWindowFrame : 
	public WindowEventHandler,
	private boost::noncopyable
{
public:
	// 
	// Ctor/Dtor
	// 
	GenericWindowFrame( );
	virtual ~GenericWindowFrame( ) = 0;

public:
	// 
	// Commands
	// 
	virtual bool PumpEvent( );
	virtual void Show( ) {}
	virtual void Hide( ) {}
	virtual void Quit( ) {}
	virtual void Maximize( ) {}
	virtual void Minimize( ) {}
	virtual void BringToFront( ) {}
	virtual void Flash( ) {}
	virtual void EnableGlobalMouseFocus( bool isEnable );

	// 
	// Sets
	// 
	virtual void SetPosition( int32_t x, int32_t y ) {}
	virtual void SetScale( int32_t width, int32_t height ) {}
	virtual void SetCaption( /*In*/ const wchar_t* src ) {}

	// 
	// Gets
	// 
	virtual void GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const {}
	virtual void GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const {}
	virtual void GetCaptionText( /*Out*/ wchar_t* caption ) const {}
	bool IsEnabledGlobalInputFocus( ) const;
	bool IsClosed( ) const;

protected:
	//
	// Protected variables
	//
	bool m_closed;
	bool m_enabledGlobalMouseFocus;
	uint32_t m_backgroundColor;
};


} /*namespace tgon*/