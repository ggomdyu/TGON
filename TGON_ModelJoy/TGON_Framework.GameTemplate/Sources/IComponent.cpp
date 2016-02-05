#include "stdafx.h"
#include "IComponent.h"

tgon::IComponent::IComponent( )
{

}


tgon::IComponent::~IComponent( )
{
}


void tgon::IComponent::SetOwner( IObject* pOwner )
{
	m_pOwner = pOwner;
}


tgon::IObject* tgon::IComponent::GetOwner( )
{
	return m_pOwner;
}
