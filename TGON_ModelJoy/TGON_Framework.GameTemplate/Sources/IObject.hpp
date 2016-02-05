#pragma once
#include "IObject.h"

#include <Console\tgConsole.h>


template <typename T>
T* tgon::IObject::AddComponent( T* const pComponent )
{
	IComponent* pComponent = new T;
	m_mapComponents.insert( std::make_pair( IComponent::GetComponentKey<T>( ), pComponent ));

	pComponent->SetOwner( this );
	return pComponent;
}


template<typename T>
T* tgon::IObject::GetComponent( )
{
	auto iter = m_mapComponents.find( IComponent::GetComponentKey<T>( ));

	if ( iter != m_mapComponents.end( )) {
		return static_cast<T*>( iter->second );
	}
	else {
		tgon::tgConsole::WriteLine( L"Unable to find component. ( ", typeid( T ).name( ) , " )" );
	}

	return nullptr;
}
