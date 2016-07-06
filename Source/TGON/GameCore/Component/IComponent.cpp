#include "PrecompiledHeader.h"
#include "IComponent.h"

#include "../Object/TGameObject.h"


tgon::IComponent::IComponent( TGameObject* owner ) :
	m_owner( owner )
{
}

tgon::IComponent::~IComponent( )
{
};