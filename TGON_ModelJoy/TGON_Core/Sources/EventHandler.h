/*
* 작성자 : 차준호
* 작성일 : 2016-01-10
* 최종 수정 : 
* 최종 수정일 : 
*/

#pragma once
#include "delegate.h"
#include <vector>

namespace tgon {


typedef void* object;

enum EventArgs
{
	Empty,
};


class EventHandler
{
	typedef void( EvhParam )( tgon::object, EventArgs );

public:
	EventHandler( ) { }
	EventHandler( const delegate<EvhParam>& rhs )		{ operator+=( rhs ); }

	void	operator=( const delegate<EvhParam>& rhs )		{ m_evhTable.clear( ); m_evhTable.push_back( rhs ); }
	void	operator+=( const delegate<EvhParam>& rhs )	{ m_evhTable.push_back( rhs ); }

	bool	operator==( std::nullptr_t ) const		{ return ( m_evhTable.empty( )); }
	bool	operator!=( std::nullptr_t ) const		{ return ( !m_evhTable.empty( )); }

	void	operator( )( object sender, EventArgs e )	{ Invoke( sender, e ); }

public:
	void Invoke( object sender, EventArgs e )
	{
		for ( auto& elem: m_evhTable )
			elem.Invoke( sender, e );
	}

private:
	std::vector<delegate<EvhParam>> m_evhTable;
};


}