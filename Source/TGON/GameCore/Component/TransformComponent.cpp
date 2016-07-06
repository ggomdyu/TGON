#include "PrecompiledHeader.h"
#include "TransformComponent.h"


tgon::TransformComponent::TransformComponent( TGameObject* owner ) :
	IComponent( owner )
{
}

tgon::TransformComponent::~TransformComponent( )
{
}


void tgon::TransformComponent::Update( float tickTime )
{
}
