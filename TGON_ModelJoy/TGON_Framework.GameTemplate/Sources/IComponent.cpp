#include "stdafx.h"
#include "IComponent.h"


tgon::IComponent::IComponent( )
{
}


tgon::IComponent::~IComponent( )
{
}


void tgon::IComponent::SetOwner( IObject* const owner )
{
	m_owner = owner;
}


tgon::IObject* tgon::IComponent::GetOwner( )
{
	return m_owner;
}
