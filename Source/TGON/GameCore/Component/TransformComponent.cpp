#include "PrecompiledHeader.h"
#include "TransformComponent.h"


tgon::TransformComponent::TransformComponent( GameObject* owner ) :
	IComponent( owner )
{
}

tgon::TransformComponent::~TransformComponent( )
{
}


void tgon::TransformComponent::Update( float tickTime )
{
}
