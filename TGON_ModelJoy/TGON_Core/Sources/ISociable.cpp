//#include "stdafx.h"
#include "ISociable.h"

#include "SociableManager.h"
 
tgon::ISociable::ISociable( uint32_t key, const SociableEnum sociableType ) :
	m_key( key ), m_sociableType( sociableType )
{
	SociableManager::GetInstance( )->RegisterMember( this );
}

tgon::ISociable::~ISociable( )
{
}