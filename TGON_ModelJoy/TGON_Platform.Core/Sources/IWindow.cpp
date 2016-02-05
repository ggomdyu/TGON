#include "stdafx.h"
#include "IWindow.h"

namespace tgon {
namespace Window
{

class Eventable : public IEventable
{
public:
	virtual bool	PullEvent( _Out_ tgon::Window::WindowEvent* outEvent ) override;

protected:
	virtual void	SetEvent( const tgon::Window::WindowEvent wndEvent );

private:
	std::unordered_multiset<unsigned int>	m_evSet;
};
class Uneventable : public IEventable
{
public:
	virtual bool	PullEvent( _Out_ tgon::Window::WindowEvent* outEvent ) override
	{
		return false;
	}

protected:
	virtual void	SetEvent( const tgon::Window::WindowEvent wndEvent )	{}
};

}
}


bool tgon::Window::Eventable::PullEvent( _Out_ tgon::Window::WindowEvent* outEvent )
{
	const auto first_iter = m_evSet.begin( );
	const auto not_exist_iter = m_evSet.end( );

	if ( first_iter != not_exist_iter )
	{
		*outEvent = *first_iter;
		m_evSet.erase( m_evSet.begin( ));
	
		return true;
	}
	else
	{
		return false;
	}
}


void tgon::Window::Eventable::SetEvent( const tgon::Window::WindowEvent wndEvent )
{
	m_evSet.insert( wndEvent );
}


tgon::Window::IWindow::IWindow( bool isEventable )
{
	if ( isEventable ) {
		m_pEventable.reset( new Eventable );
		//m_pEventable.reset( new Eventable );
	}
	else
	{
		m_pEventable.reset( new Uneventable );
		//m_pEventable.reset( new Uneventable );
	}
}

tgon::Window::IWindow::~IWindow( )
{
}