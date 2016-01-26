#include "stdafx.h"
#include "IWindow.h"


tgon::IWindow::IWindow( const WindowStyle& wndStyle ) :
	m_wndStyle( wndStyle )
{
}


tgon::IWindow::~IWindow( )
{
}


void tgon::IWindow::AddEventCallback( unsigned int evType, const EventProc& evProc )
{
	m_evTable.insert( std::make_pair( evType, evProc ));
}


void tgon::IWindow::CallEventProc( unsigned int evType )
{
	auto findElem = m_evTable.find( evType );
	const auto notExistElem = m_evTable.end( );

	while (( findElem != notExistElem ) && ( findElem->first == evType ))
	{
		findElem->second( );

		++findElem;
	}
}
