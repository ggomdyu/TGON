#pragma once
#include "IComponent.h"

template<typename T>
inline uint32_t tgon::IComponent::GetIdentifier( )
{
	static const auto keyCode( typeid(T).hash_code( ));
	return keyCode;
}