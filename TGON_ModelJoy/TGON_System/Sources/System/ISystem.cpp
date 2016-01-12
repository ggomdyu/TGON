#include "stdafx.h"
#include "ISystem.h"

#include "SociableManager.h"


tgon::ISystem::ISystem( unsigned int key ) :
	ISociable( key, SociableEnum::Social_System )
{
}


tgon::ISystem::~ISystem( )
{
}