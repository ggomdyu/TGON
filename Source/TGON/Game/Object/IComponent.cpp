#include "PrecompiledHeader.h"
#include "IComponent.h"

#include "../Object/TGameObject.h"


tgon::IComponent::IComponent( GameObject* owner ) :
	m_owner( owner )
{
}

tgon::IComponent::~IComponent( )
{
};