/*
* 작성자 : 차준호
* 작성일 : 2016-01-09
* 최종 수정 : 
* 최종 수정일 :
*/
#pragma once
#include <memory>
#include <unordered_set>

#include "WindowEvent.h"


namespace tgon {
namespace Window {

class IEventable
{
public:
	virtual bool	PullEvent( tgon::Window::WindowEvent* outEvent ) = 0;
	virtual void	SetEvent( const tgon::Window::WindowEvent wndEvent ) = 0;
};

class IWindow
{
public:
	bool	PullEvent( _Out_ WindowEvent* outEvent )	{ return m_pEventable->PullEvent( outEvent ); }

//protected:
	void	SetEvent( const tgon::Window::WindowEvent wndEvent )		{ m_pEventable->SetEvent( wndEvent ); }


public:
	virtual void	Show( ) = 0;
	virtual void	BringToTop( ) = 0;
	virtual void	SetPosition( const int x, const int y ) = 0;
	virtual void	Move( const int x, const int y ) = 0;
	virtual void	Exit( ) = 0;

public:
	virtual void	GetPosition( int* x, int* y ) = 0;

protected:
	IWindow( bool isEventable );
	virtual ~IWindow( ) = 0;

private:
	std::unique_ptr<IEventable>	m_pEventable;
};


}
}