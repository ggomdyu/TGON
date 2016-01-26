/*
* 작성자 : 차준호
* 작성일 : 2016-01-09
* 최종 수정 : 
* 최종 수정일 :
*/
#pragma once
#include <functional>
#include <unordered_map>
#include "WindowStyle.h"
#include "WindowEvent.h"


namespace tgon {


class IWindow
{
protected:
	typedef std::function<void()> EventProc;
	typedef std::unordered_multimap<unsigned int, EventProc> EventProcTable;

public:
	virtual void		FrameMove( ) = 0;

public:
	virtual void		Show( ) = 0;
	virtual void		BringToTop( ) = 0;
	virtual void		SetPosition( int x, int y ) = 0;
	virtual void		Move( int x, int y ) = 0;
	virtual void		Exit( ) = 0;

	void				AddEventCallback( unsigned int evType, const EventProc& evProc );

public:
	virtual const WindowEvent		GetWindowEvent( ) const = 0;
	const WindowStyle&				GetWindowStyle( )	 const				{ return m_wndStyle; }


protected:
	explicit			IWindow( const WindowStyle& );
	virtual				~IWindow( ) = 0;

	void 				CallEventProc( unsigned int evType );

private:
	WindowStyle		m_wndStyle;
	EventProcTable		m_evTable;
};


}