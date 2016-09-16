/*
* Author : Cha Junho
* Date : 01/09/2016
* Latest author : 
* Latest date :
*/


#pragma once
#include "../OSAL/PlatformInclude.h"
#include "../Abstract/APlatformWindowEventHandler.h"

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>
#include <cstdint>


namespace tgon
{


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

	/* @note	If true, then make resize frame to window. */
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

class TGON_API APlatformWindow : 
	private boost::noncopyable
{
	// 
	// Ctor/Dtor
	// 
protected:
	APlatformWindow( );
	virtual ~APlatformWindow( ) = 0;


	// 
	// Commands
	// 
public:
	virtual bool PumpEvent( ) { return false; }
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
	void SetEventHandler( /*In*/ const std::shared_ptr<AWindowEventHandler>& eventHandler );

	// 
	// Gets
	// 
	virtual void GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const {}
	virtual void GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const {}
	virtual void GetCaptionText( /*Out*/ wchar_t* caption ) const {}
	bool IsEnabledGlobalInputFocus( ) const;
	bool IsClosed( ) const;

	//
	// rotected variables
	//
protected:
	bool m_enabledGlobalMouseFocus;
	bool m_closed;
	uint32_t m_backgroundColor;
	std::shared_ptr<AWindowEventHandler> m_eventListener;
};


inline void APlatformWindow::EnableGlobalMouseFocus( bool isEnable )
{
	m_enabledGlobalMouseFocus = isEnable;
}

inline void APlatformWindow::SetEventHandler( /*In*/ const std::shared_ptr<AWindowEventHandler>& eventListener )
{
	m_eventListener = eventListener;
}

inline bool APlatformWindow::IsEnabledGlobalInputFocus( ) const
{
	return m_enabledGlobalMouseFocus;
}

inline bool APlatformWindow::IsClosed( ) const
{
	return m_closed;
}


} /*namespace tgon*/