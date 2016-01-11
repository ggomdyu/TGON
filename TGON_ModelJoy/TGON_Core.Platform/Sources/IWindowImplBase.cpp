#include "stdafx.h"
#include "IWindowImplBase.h"


tgon::IWindowImplBase::IWindowImplBase( const WindowStyle& wndStyle ) :
	m_wndStyle( wndStyle )
{
}

tgon::IWindowImplBase::~IWindowImplBase( )
{
}

void tgon::IWindowImplBase::AddEventCallback( uint32_t evType, const EventProc& evProc )
{
	m_evTable.insert( std::make_pair( evType, evProc ));
}

void tgon::IWindowImplBase::CallEventProc( uint32_t evType )
{
	const auto findElem = m_evTable.find( evType );
	const auto notExist = m_evTable.end( );

	if ( findElem != notExist )
	{
		findElem->second( );
	}
}
