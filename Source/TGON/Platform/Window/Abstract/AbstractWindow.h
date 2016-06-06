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
	

class TGON_API AbstractWindow :
	private boost::noncopyable
{
	friend class AbstractApplication;

protected:
	AbstractWindow( const WindowStyle& wndStyle );
	virtual ~AbstractWindow( ) = 0;

public:
	/*
		Commands
	*/
	void Show( );
	void Hide( );
	void Close( );
	void Maximize( );
	void Minimize( );
	void BringToTop( ) {};
	void Flash( ) {};

	/*
		Sets
	*/
	void SetPosition( int32_t x, int32_t y );
	void SetScale( int32_t width, int32_t height );
	void SetCaption( const wchar_t* title );

	/*
		Event handler
	*/
	virtual void OnShow( ) {}
	virtual void OnHide( ) {}
	virtual void OnGetFocus( ) {}
	virtual void OnLostFocus( ) {}
	virtual void OnMaximized( ) {}
	virtual void OnMinimized( ) {}
	virtual void OnIdle( ) = 0;	// Must be implemented
	virtual void OnMove( int x, int y ) {}
	virtual void OnSize( int width, int height ) {}
	virtual void OnMouseMove( int x, int y ) {}
	virtual void OnLMouseDown( int x, int y ) {}
	virtual void OnLMouseUp( int x, int y ) {}
	virtual void OnRMouseDown( int x, int y ) {}
	virtual void OnRMouseUp( int x, int y ) {}
	virtual void OnMMouseDown( int x, int y ) {}
	virtual void OnMMouseUp( int x, int y ) {}
	virtual void OnMouseLeave( ) {}
	virtual void OnMouseEnter( ) {}

	/*
		Gets
	*/
	static int32_t GetCreationCount( );
	void GetPosition( int32_t* x, int32_t* y ) const;
	void GetSize( int32_t* width, int32_t* height ) const;
	const char* GetCaption( ) const;
	

protected:
	SDL_Window* GetSDLWindow( );
	const SDL_Window* GetSDLWindow( ) const;
	const WindowStyle& GetWindowStyle( ) const;

private:
	void SetupWindow( );

private:
	WindowStyle m_wndStyle;
	SDL_Window* m_sdlWindow;
	static int32_t ms_sdlWindowCount;
};

inline int32_t AbstractWindow::GetCreationCount( )
{
	return ms_sdlWindowCount;
}

inline void AbstractWindow::Show( )
{
	SDL_ShowWindow( m_sdlWindow );
}

inline void AbstractWindow::Hide( )
{
	SDL_HideWindow( m_sdlWindow );
}

inline void AbstractWindow::Close( )
{
	SDL_DestroyWindow( m_sdlWindow );
}

inline void tgon::AbstractWindow::Maximize( )
{
	SDL_MaximizeWindow( m_sdlWindow );
}

inline void AbstractWindow::Minimize( )
{
	SDL_MinimizeWindow( m_sdlWindow );
}

inline void AbstractWindow::GetPosition( 
	int32_t* x, 
	int32_t* y ) const
{
	SDL_GetWindowPosition( m_sdlWindow, x, y );
}

inline void AbstractWindow::GetSize( 
	int32_t* width, 
	int32_t* height ) const
{
	SDL_GetWindowSize( m_sdlWindow, width, height );
}

inline const char* AbstractWindow::GetCaption( ) const
{
	return SDL_GetWindowTitle( m_sdlWindow );
}

inline SDL_Window* AbstractWindow::GetSDLWindow( )
{
	return m_sdlWindow;
}

inline const SDL_Window* AbstractWindow::GetSDLWindow( ) const
{
	return m_sdlWindow;
}

inline const WindowStyle& tgon::AbstractWindow::GetWindowStyle( ) const
{
	return m_wndStyle;
}


}