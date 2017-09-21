/*
* Author : Junho-Cha
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Core/Object/Object.h"
#include "../Core/Math/Mathf.h"

#include "../Component/TransformComponent.h"


namespace tgon
{


class TGON_API GameObject :
	public Object
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( GameObject, std::nullptr_t )


	// 
	// Ctor/Dtor
	// 
public:
	GameObject( );
	GameObject( const GameObject& ) = delete;
	virtual ~GameObject( );

	/*
		Operators
	*/
	GameObject& operator=( const GameObject& ) = delete;


public:
};

//class TransformComponent;
//	/*
//		Sets
//	*/
//	template <typename ComponentTy> void AddComponent( ComponentTy* );
//	
//	/*
//		Gets
//	*/
//	template <typename ComponentTy> ComponentTy* GetComponent( );
//
//private:
//	TransformComponent* m_transformComponent;
//
//	std::map<uint32_t, IComponent*> m_components;
//
//template<>
//inline void GameObject::AddComponent( TransformComponent* newComponent ) = delete;
//
//template<typename ComponentTy>
//inline void GameObject::AddComponent( ComponentTy* component )
//{
//	//const auto identifier = newComponent->GetComponentID( );
//
//	//m_components.insert( std::make_pair( identifier, newComponent ));
//	//newComponent->SetOwner( this );
//}
////////////////////////////////////////////
//template<typename _Ty>
//inline void TGameObject::AddComponent( _Ty * )
//{
//	/*auto iter = m_components.find( IComponent::GetIdentifier<T>( ));
//	if ( iter != m_components.end( )) {
//		return static_cast<T*>( iter->second );
//	}
//	else {
//		TConsole::WriteLine( L"Unable to find component. ( ", typeid( T ).name( ), L" )" );
//	}
//*/
//	return nullptr;
//}

//template<>
//inline TransformComponent* GameObject::GetComponent( )
//{	
//	return m_transformComponent;
//}


}