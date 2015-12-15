//#include "stdafx.h"
#include "ISystem.h"

#include "SociableManager.h"

tgon::ISystem::ISystem( uint32_t systemKey ) :
	ISociable( systemKey, SociableEnum::Social_System )
{
	SociableManager::GetInstance( )->RegisterMember( this );
}


tgon::ISystem::~ISystem( )
{
}

void tgon::ISystem::Initialize( )
{
}
