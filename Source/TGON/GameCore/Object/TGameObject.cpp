#include "PrecompiledHeader.h"
#include "TGameObject.h"

#include "../Component/TransformComponent.h"


tgon::TGameObject::TGameObject( ) :
	m_transformComponent( new TransformComponent( this ))
{
}

tgon::TGameObject::~TGameObject( )
{
}