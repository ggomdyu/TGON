/*
* Author : Junho-Cha
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Core/Reflection/TObject.h"
#include "../Core/Math/TMath.h"
#include "../Platform/Console/TConsole.h"

#include "../Component/TransformComponent.h"


namespace tgon
{

class TGON_API TGameObject :
	public TObject
{
public:
	TGON_OBJECT( TGameObject, TObject )

	/*
		Constructor
	*/
	TGameObject( );

	TGameObject( const TGameObject& ) = delete;
	
	/*
		Destructor
	*/
	virtual ~TGameObject( );

	/*
		Operators
	*/
	TGameObject& operator=( const TGameObject& ) = delete;


public:
	/*
		Sets
	*/
	template <typename _Ty> void AddComponent( _Ty* );
	
	/*
		Gets
	*/
	template <typename _Ty> _Ty* GetComponent( );

private:
	std::unique_ptr<class TransformComponent> m_transformComponent;

	std::map<uint32_t, class IComponent*> m_components;
};


template<>
inline void TGameObject::AddComponent( TransformComponent* newComponent ) = delete;

template<typename T>
inline void TGameObject::AddComponent( T* component )
{

	//const auto identifier = newComponent->GetComponentID( );

	//m_components.insert( std::make_pair( identifier, newComponent ));
	//newComponent->SetOwner( this );
}

//template<typename T>
//T* TObject::GetComponent( )
//{
//	auto iter = m_components.find( IComponent::GetIdentifier<T>( ));
//
//	if ( iter != m_components.end( )) {
//		return static_cast<T*>( iter->second );
//	}
//	else {
//		TConsole::WriteLine( L"Unable to find component. ( ", typeid( T ).name( ), L" )" );
//	}
//
//	return nullptr;
//}

//template <> 
//std::unique_ptr<TransformComponent>& TGameObject::GetComponent( )//->decltype( m_transformComponent.get( ))
//{
//	return m_transformComponent.get();
//}


}