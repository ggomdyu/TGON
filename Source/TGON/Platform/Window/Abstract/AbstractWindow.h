/*
* Author : Junho-Cha
* Date : 01/09/2016
* Latest author : 
* Latest date :
*/


#pragma once
#include <cstdint>
#include "../../../Platform/Config/Build.h"
#include "../WindowStyle.h"


namespace tgon
{


class TGON_API AbstractWindow : 
	private boost::noncopyable
{
protected:
	explicit AbstractWindow( const WindowStyle& wndStyle );

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


	/*
		Sets
	*/
	virtual void SetPosition( int32_t x, int32_t y ) {};

	virtual void SetScale( int32_t width, int32_t height ) {};

	virtual void SetCaption( const wchar_t* src ) {};

	/*
		Gets
	*/
	virtual void GetPosition( int32_t* x, int32_t* y ) const {};

	virtual void GetSize( int32_t* width, int32_t* height ) const {};

	virtual void GetCaption( wchar_t* caption ) const {}

	virtual bool IsDestroyed( ) const { return false; }


	/*
		Event handlers
	*/

	virtual void OnClose( ) {}

	virtual void OnIdle( ) = 0;	// Must be implemented

	virtual void OnMove( int x, int y ) {}

	virtual void OnSize( int width, int height ) {}

	virtual void OnMouseMove( int x, int y ) {}

	virtual void OnLMouseDown( int x, int y ) {}

	virtual void OnLMouseUp( int x, int y ) {}

	virtual void OnRMouseDown( int x, int y ) {}

	virtual void OnRMouseUp( int x, int y ) {}


protected:
	const WindowStyle& GetWindowStyle( ) const;

private:
	WindowStyle m_wndStyle;
};

inline const WindowStyle& tgon::AbstractWindow::GetWindowStyle( ) const
{
	return m_wndStyle;
}


}