#pragma once
#include "IObject.h"
#include <TConsole.h>


template <typename T>
T* tgon::IObject::AddComponent( T* pComponent )
{
	IComponent* pComponent = new T;
	m_components.insert( std::make_pair( IComponent::GetIdentifier<T>( ), pComponent ));

	pComponent->SetOwner( this );
	return pComponent;
}


template<typename T>
T* tgon::IObject::GetComponent( )
{
	auto iter = m_components.find( IComponent::GetIdentifier<T>( ));

	if ( iter != m_components.end( )) {
		return static_cast<T*>( iter->second );
	}
	else {
		TConsole::WriteLine( L"Unable to find component. ( ", typeid( T ).name( ), L" )" );
	}

	return nullptr;
}
