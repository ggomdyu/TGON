//#include "stdafx.h"
#include "ISociable.h"

#include "SociableManager.h"

tgon::ISociable::ISociable( const SociableEnum sociableType ) :
	m_sociableType( sociableType )
{
}

tgon::ISociable::ISociable( const std::string& name, const SociableEnum sociableType ) :
	m_name( name ), m_sociableType( sociableType )
{
	SociableManager::GetInstance( )->RegisterMember( this );
}

tgon::ISociable::ISociable( std::string&& name, const SociableEnum sociableType ) :
	m_name( std::move( name )), m_sociableType( sociableType )
{
	SociableManager::GetInstance( )->RegisterMember( this );
}

tgon::ISociable::~ISociable( )
{
}