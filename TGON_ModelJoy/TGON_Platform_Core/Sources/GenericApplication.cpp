#include "stdafx.h"
#include "GenericApplication.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <memory>
	#include <cassert>
#endif

NSBEGIN( tgon );
decltype( GenericApplication::m_wndRepository ) GenericApplication::m_wndRepository;

void GenericApplication::AddWindow( const std::string& key,
									_In_ const std::shared_ptr<Window>& window )
{
	// not mistake
	assert( m_wndRepository.find( key ) == m_wndRepository.end( ));

	m_wndRepository.insert( std::make_pair( key, window ));
}

const std::shared_ptr<Window> GenericApplication::GetWindow( const std::string& key )
{
	decltype( m_wndRepository )::iterator iter = m_wndRepository.find( key );

	if ( iter != m_wndRepository.end( ))
		return iter->second;
	return nullptr;
}
NSEND( );