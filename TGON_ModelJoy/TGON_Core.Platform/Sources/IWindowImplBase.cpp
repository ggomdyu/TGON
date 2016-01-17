#include "stdafx.h"
#include "IWindowImplBase.h"


tgon::IWindowImplBase::IWindowImplBase( const WindowStyle& wndStyle ) :
	m_wndStyle( wndStyle )
{
}


tgon::IWindowImplBase::~IWindowImplBase( )
{
}


void tgon::IWindowImplBase::AddEventCallback( unsigned int evType, const EventProc& evProc )
{
	m_evTable.insert( std::make_pair( evType, evProc ));
}


void tgon::IWindowImplBase::CallEventProc( unsigned int evType )
{
	auto findElem = m_evTable.find( evType );
	const auto notExistElem = m_evTable.end( );

	while (( findElem != notExistElem ) && ( findElem->first == evType ))
	{
		findElem->second( );

		++findElem;
	}
}
