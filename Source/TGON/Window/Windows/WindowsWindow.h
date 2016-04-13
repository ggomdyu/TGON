/*
* Author : Junho-Cha
* Date : 2015-11-12
* Latest author :
* Latest date :
*/

#pragma once
#include "../Layered/LayeredWindow.h"

#include <stdint.h>
#include <functional>
#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


class WindowsWindow;
typedef WindowsWindow WindowImpl;


/*
	- Why inherited as private?
	1. Abstraction window is logically uncorrect.
	( It just my thought. Some of engines using as public inherited )

	2. To induce inlining of virtual functions
*/

class WindowsWindow : private LayeredWindow
{
public:
	static const TCHAR WndClassName[];


	/*
		@ Cons/Destructors
	*/
protected:
	explicit WindowsWindow( const struct WindowStyle& );
	virtual ~WindowsWindow( );
private:
	explicit WindowsWindow( const WindowsWindow& ) = delete;
	WindowsWindow& operator=( const WindowsWindow& ) = delete;


	/*
		@ commands
	*/
public:
	// Sets
	virtual void Quit( ) override;
	virtual void Show( ) override;
	virtual void Hide( ) override;
	virtual void Maximize( ) override;
	virtual void Minimize( ) override;
	virtual void BringToTop( ) override;
	virtual void FlashWindow( ) override;
	virtual void SetPosition( const int32_t x,
							  const int32_t y ) override;
	virtual void SetSize( const int32_t width,
						  const int32_t height ) override;
	virtual void SetCaption( const wchar_t* const src );

	// Gets
	virtual bool IsQuitted( ) const;
	virtual void GetPosition( int32_t* const x,
							  int32_t* const y ) const override;
	virtual void GetSize( int32_t* const width,
						  int32_t* const height ) const override;
	virtual std::wstring GetCaption( ) const override;


	HWND GetWindowHandle( ) const  { return m_wndHandle; }


	/*
		@ Internal work
	*/
protected:
	virtual void LazyInitialize( ) override;

private:
	void CreateWindowForm( const struct WindowStyle& );
	void AdditionalInit( const struct WindowStyle& );

	static LRESULT WINAPI UneventableMsgProc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT WINAPI EventableMsgProc( HWND, UINT, WPARAM, LPARAM );

	/*
		@ Protected data area
	*/
private:
	HWND m_wndHandle;
	bool m_isDestroyed;

	std::function<int32_t( class TWindow*, enum struct WindowEvent )> m_msgCallback;
};


}


#include "WindowsWindow.hpp"