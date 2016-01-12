#include "stdafx.h"
#include "ISociable.h"

#include "SociableManager.h"
 
tgon::ISociable::ISociable( unsigned int key, SociableEnum sociableType ) :
	m_key( key ), m_sociableType( sociableType )
{
	SociableManager::GetInstance( )->RegisterMember( this );
}


tgon::ISociable::~ISociable( )
{
}