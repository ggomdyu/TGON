#include "stdafx.h"
#include "GenericApplication.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <memory>
	#include <cassert>
#endif

tgon::GenericApplication::WindowContainer tgon::GenericApplication::m_wndRepo;

void tgon::GenericApplication::AddWindow( _In_ const std::string& key, _In_ const sspWindow& window )
{
	// not mistake
	assert( m_wndRepo.find( key ) == m_wndRepo.end( ));

	m_wndRepo.insert( std::make_pair( key, window ));
}

const std::shared_ptr<tgon::Window>tgon::GenericApplication::GetWindow( _In_ const std::string& key )
{
	WindowContainer::iterator iter = m_wndRepo.find( key );

	if ( iter != m_wndRepo.end( ))
		return iter->second;
	return nullptr;
}