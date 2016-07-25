/*
* Author : Junho-Cha
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Core/Object/TObject.h"
#include "../Core/Math/TMath.h"

#include "../Component/TransformComponent.h"


namespace tgon
{


class TransformComponent;

class TGON_API TGameObject :
	public TObject
{
public:
	TGON_OBJECT( TGameObject, std::nullptr_t )


public:
	/*
		Cons/Destructor
	*/
	TGameObject( );

	TGameObject( const TGameObject& ) = delete;
	
	virtual ~TGameObject( );

	/*
		Operators
	*/
	TGameObject& operator=( const TGameObject& ) = delete;


public:
	/*
		Sets
	*/
	template <typename ComponentTy> void AddComponent( ComponentTy* );
	
	/*
		Gets
	*/
	template <typename ComponentTy> ComponentTy* GetComponent( );

private:
	TransformComponent* m_transformComponent;

	std::map<uint32_t, IComponent*> m_components;
};


template<>
inline void TGameObject::AddComponent( TransformComponent* newComponent ) = delete;

template<typename ComponentTy>
inline void TGameObject::AddComponent( ComponentTy* component )
{
	//const auto identifier = newComponent->GetComponentID( );

	//m_components.insert( std::make_pair( identifier, newComponent ));
	//newComponent->SetOwner( this );
}

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

template<>
inline TransformComponent* TGameObject::GetComponent( )
{	
	return m_transformComponent;
}


}