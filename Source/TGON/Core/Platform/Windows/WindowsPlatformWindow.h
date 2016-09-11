/*
* Author : Cha Junho
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../Abstract/APlatformWindow.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>


namespace tgon
{


// todo: Inherit IDropTarget

class TGON_API WindowsPlatformWindow : 
	public APlatformWindow
{
	friend class WindowsPlatformApplication;

	// 
	// Ctor/Dtor
	// 
public:
	explicit WindowsPlatformWindow( /*In*/ const WindowStyle& wndStyle );
	virtual ~WindowsPlatformWindow( );

	// 
	// Commands
	// 
public:
	bool PumpEvent( );
	void Show( );
	void Hide( );
	void Quit( );
	void Maximize( );
	void Minimize( );
	void BringToFront( );
	void Flash( );

	// 
	// Sets
	// 
	void EnableGlobalMouseFocus( bool isEnable );
	void SetPosition( int32_t x, int32_t y );
	void SetScale( int32_t width, int32_t height );
	void SetCaption( /*In*/ const wchar_t* caption );

	// 
	// Gets
	// 
	void GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const;
	void GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const;
	void GetCaption( /*Out*/ wchar_t* caption ) const;
	HWND GetWindowHandle( ) const;

	// 
	// Internal works
	// 
private:
	void AdditionalInit( /*In*/ const WindowStyle& );
	virtual LRESULT ProcessMessage( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	// 
	// Private variables
	// 
private:
	HWND m_wndHandle;

};

using TPlatformWindow = WindowsPlatformWindow;


} /*namespace tgon*/