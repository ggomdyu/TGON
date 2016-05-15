#include "PrecompiledHeader.h"
#include "SceneSystem.h"

#include "../Scene/DefaultScene.h"


tgon::SceneSystem::SceneSystem( ) :
	m_currScene( new DefaultScene )
{
}

tgon::SceneSystem::~SceneSystem( )
{
	m_currScene.release( );
}

void tgon::SceneSystem::LoadScene( IScene* newScene )
{
	m_currScene.reset( newScene );
}

void tgon::SceneSystem::Update( float tickTime )
{
	if ( m_currScene )
	{
		m_currScene->Update( tickTime );
		m_currScene->Render( );
	}
}