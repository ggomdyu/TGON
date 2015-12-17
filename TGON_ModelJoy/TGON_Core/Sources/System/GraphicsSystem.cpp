//#include "stdafx.h"
#include "GraphicsSystem.h"


Implement_Root_RTTI( tgon::GraphicsSystem )


tgon::GraphicsSystem::GraphicsSystem( ) :
	ISystem( RTTI::GetTypeHash<GraphicsSystem>( ))
{
}


tgon::GraphicsSystem::~GraphicsSystem( )
{
}

void tgon::GraphicsSystem::Initialize( )
{
}


void tgon::GraphicsSystem::FrameMove( float elapsedTime )
{
}

void tgon::GraphicsSystem::RecvMessage( _In_ const SociableMessage& msg )
{
}