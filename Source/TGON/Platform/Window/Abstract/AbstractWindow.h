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
	boost::noncopyable
{
public:
	virtual void Make( ) = 0;

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

	/*
		Gets
	*/
	virtual void GetPosition( _Out_ int32_t* x, 
							  _Out_ int32_t* y ) const {};
	virtual void GetSize( _Out_ int32_t* width, 
						  _Out_ int32_t* height ) const {};

	virtual void GetCaption( _Out_ wchar_t* caption ) const {}

	virtual bool IsDestroyed( ) { return false; }

	/*
		EventHandler
	*/
	virtual void OnCreate( ) {}
	virtual void OnClose( ) {}
	virtual void OnIdle( ) = 0;	// Must be implemented
	virtual void OnDestroy( ) {}
	virtual void OnMove( int x, int y ) {}
	virtual void OnSize( int width, int height ) {}
	virtual void OnMouseMove( int x, int y ) {}
	virtual void OnLMouseDown( int x, int y ) {}
	virtual void OnLMouseUp( int x, int y ) {}
	virtual void OnRMouseDown( int x, int y ) {}
	virtual void OnRMouseUp( int x, int y ) {}


protected:
	const WindowStyle& GetWindowStyle( ) const;
	bool IsEventHandleable( ) const;

public:
	AbstractWindow( const WindowStyle& wndStyle, 
			 bool isEventHandleable );
	virtual ~AbstractWindow( ) = 0;

private:
	WindowStyle m_wndStyle;
	bool m_isEventHandleable;
};


inline const WindowStyle& tgon::AbstractWindow::GetWindowStyle( ) const
{
	return m_wndStyle;
}

inline bool AbstractWindow::IsEventHandleable( ) const
{
	return m_isEventHandleable;
}


}