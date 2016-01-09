#include "stdafx.h"
#include "ISystem.h"

#include "SociableManager.h"


tgon::ISystem::ISystem( uint32_t key ) :
	ISociable( key, SociableEnum::Social_System )
{
}


tgon::ISystem::~ISystem( )
{
}