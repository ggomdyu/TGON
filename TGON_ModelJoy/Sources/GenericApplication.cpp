#include "stdafx.h"
#include "GenericApplication.h"

NSBEGIN( tgon );
decltype( GenericApplication::m_windowRepository ) GenericApplication::m_windowRepository;

void GenericApplication::AddWindow( const std::string& key,
									_In_ const std::shared_ptr<PlatformWindow>& window )
{
	// It's Intended code; not mistake
	assert( m_windowRepository.find( key ) == m_windowRepository.end( ));

	m_windowRepository.insert( std::make_pair( key, window ));
}

const std::shared_ptr<PlatformWindow> GenericApplication::GetWindow( const std::string& key )
{
	decltype( m_windowRepository )::iterator iter = m_windowRepository.find( key );

	if ( iter != m_windowRepository.end( ))
		return iter->second;
	return nullptr;
}
NSEND( );