/*
* Author : Junho-Cha
* Date : 01/09/2016
* Latest author : 
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"
#include "../WindowStyle.h"


namespace tgon
{
	

class TGON_API AbstractWindowDelegate
{
public:
	virtual void OnCreate( ) {}
	virtual void OnDestroy( ) {}
	virtual void OnClose( ) {}
	virtual void OnIdle( ) = 0;	// Must be implemented
	virtual void OnMove( int x, int y ) {}
	virtual void OnSize( int width, int height ) {}
	virtual void OnMouseMove( int x, int y ) {}
	virtual void OnLMouseDown( int x, int y ) {}
	virtual void OnLMouseUp( int x, int y ) {}
	virtual void OnRMouseDown( int x, int y ) {}
	virtual void OnRMouseUp( int x, int y ) {}
};

class TGON_API AbstractWindow : 
	private boost::noncopyable
{
public:
	AbstractWindow( const WindowStyle& wndStyle,
					AbstractWindowDelegate* wndDelegate );
	virtual ~AbstractWindow( ) = 0;

public:
	/*
		Commands
	*/
	virtual void Show( ) {};
	virtual void Hide( ) {};
	virtual void Quit( ) = 0;	// Must be implemented
	virtual void Maximize( ) {};
	virtual void Minimize( ) {};
	virtual void BringToTop( ) {};
	virtual void Flash( ) {};

	/*
		Sets
	*/
	virtual void SetPosition( int32_t x, 
							  int32_t y ) {};
	virtual void SetScale( int32_t width, 
						   int32_t height ) {};
	virtual void SetCaption( const wchar_t* src ) {};

	// Useable to subclassing event handler
	void SetDelegate( AbstractWindowDelegate* wndDelegate );


	/*
		Gets
	*/
	virtual void GetPosition( _Out_ int32_t* x, 
							  _Out_ int32_t* y ) const {};
	virtual void GetSize( _Out_ int32_t* width, 
						  _Out_ int32_t* height ) const {};

	virtual void GetCaption( _Out_ wchar_t* caption ) const {}

	virtual bool IsDestroyed( ) { return false; }

protected:
	const WindowStyle& GetWindowStyle( ) const;
	AbstractWindowDelegate* GetDelegate( );

private:
	WindowStyle m_wndStyle;
	AbstractWindowDelegate* m_wndDelegate;
};

inline void AbstractWindow::SetDelegate( 
	AbstractWindowDelegate* wndDelegate )
{
	m_wndDelegate = wndDelegate;
}

inline const WindowStyle& tgon::AbstractWindow::GetWindowStyle( ) const
{
	return m_wndStyle;
}

inline AbstractWindowDelegate* AbstractWindow::GetDelegate( )
{
	return m_wndDelegate;
}


}