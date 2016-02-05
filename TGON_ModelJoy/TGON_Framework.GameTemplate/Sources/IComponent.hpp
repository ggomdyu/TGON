#pragma once
#include "IComponent.h"

template<typename T>
inline unsigned int IComponent::GetComponentKey( )
{
	static const auto typeKey( typeid( T ).hash_code( ));
	return typeKey;
}