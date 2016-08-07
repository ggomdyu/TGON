/*
* Author : Cha Junho
* Date : 01/09/2016
* Latest author : 
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"

#include "../../Window/Abstract/AbstractWindowEventHandler.h"
#include <memory>


namespace tgon
{


class TGON_API AbstractWindow : 
	private boost::noncopyable
{
/*
	Cons/Destructor
*/
protected:
	AbstractWindow( );

	virtual ~AbstractWindow( ) = 0;


/*
	Commands
*/
public:
	virtual bool PumpEvent( );

	virtual void Show( );

	virtual void Hide( );

	virtual void Quit( );

	virtual void Maximize( );

	virtual void Minimize( );

	virtual void BringToTop( );

	virtual void Flash( );

	virtual void EnableGlobalMouseFocus( bool isEnable );


/*
	Sets
*/
	void SetEventHandler( /*In*/ const std::shared_ptr<AbstractWindowEventHandler>& eventHandler );

	virtual void SetPosition( int32_t x, int32_t y );

	virtual void SetScale( int32_t width, int32_t height );

	virtual void SetCaption( /*In*/ const wchar_t* src );

/*
	Gets
*/
	virtual void GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const;

	virtual void GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const;

	virtual void GetCaption( /*Out*/ wchar_t* caption ) const;

	bool IsEnabledGlobalInputFocus( ) const;

	bool IsDestroyed( ) const;

	
protected:
	bool m_enabledGlobalMouseFocus;

	bool m_destroyed;

	std::shared_ptr<AbstractWindowEventHandler> m_eventListener;
};


inline bool tgon::AbstractWindow::PumpEvent( )
{
	return false;
}

inline void tgon::AbstractWindow::Show( )
{
}

inline void tgon::AbstractWindow::Hide( )
{
}

inline void tgon::AbstractWindow::Quit( )
{
}

inline void tgon::AbstractWindow::Maximize( )
{
}

inline void tgon::AbstractWindow::Minimize( )
{
}

inline void tgon::AbstractWindow::BringToTop( )
{
}

inline void AbstractWindow::Flash( )
{
}

inline void AbstractWindow::EnableGlobalMouseFocus( bool isEnable )
{
}

inline void tgon::AbstractWindow::SetEventHandler( /*In*/ const std::shared_ptr<AbstractWindowEventHandler>& eventListener )
{
	m_eventListener = eventListener;
}

inline void AbstractWindow::SetPosition( int32_t x, int32_t y )
{
}

inline void AbstractWindow::SetScale( int32_t width, int32_t height )
{
}

inline void AbstractWindow::SetCaption( /*In*/ const wchar_t* src )
{
}

inline void AbstractWindow::GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const
{
}

inline void AbstractWindow::GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const
{
}

inline void AbstractWindow::GetCaption( /*Out*/ wchar_t* caption ) const
{
}

inline bool AbstractWindow::IsEnabledGlobalInputFocus( ) const
{
	return m_enabledGlobalMouseFocus;
}

inline bool AbstractWindow::IsDestroyed( ) const
{
	return m_destroyed;
}


}