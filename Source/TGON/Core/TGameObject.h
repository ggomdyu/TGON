/*
* Author : Junho-Cha
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <map>
#include <stdint.h>

#include "TObject.h"
#include "../Core/Math/TMath.h"
#include "../Platform/Console/TConsole.h"


namespace tgon
{

class IComponent;
class TGON_API TGameObject :
	public TObject
{
public:
	TGON_OBJECT( TGameObject, TObject )

	TGameObject( );
	virtual ~TGameObject( );

public:
	void SetPosition( const TVector3& );
	void Move( const TVector3& );
	void SetAngle( const TVector3& );
	void Rotate( const TVector3& );
	void SetScale( const TVector3& );
	void Scale( const TVector3& );

	const TVector3& GetPosition( ) const;
	const TVector3& GetAngle( ) const;
	const TVector3& GetScale( ) const;

public:
	template <typename _Ty> void AddComponent( _Ty* newComponent );
	template <typename _Ty> _Ty* GetComponent( );

private:
	TVector3 m_pos;
	TVector3 m_angle;
	TVector3 m_scale;

	std::map<uint32_t, IComponent*> m_components;
};


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


template<typename _Ty>
inline _Ty* TGameObject::GetComponent( )
{
	return NULL;
}

inline void tgon::TGameObject::SetPosition( const TVector3& pos )
{
	m_pos = pos;
}

inline void tgon::TGameObject::Move( const TVector3& pos )
{
	m_pos += pos;
}

inline void tgon::TGameObject::SetAngle( const TVector3& rot )
{
	m_angle = rot;
}

inline void tgon::TGameObject::Rotate( const TVector3& rot )
{
	m_angle += rot;
}

inline void tgon::TGameObject::SetScale( const TVector3& scale )
{
	m_scale = scale;
}

inline void tgon::TGameObject::Scale( const TVector3& scale )
{
	m_scale += scale;
}

inline const TVector3& TGameObject::GetPosition( ) const
{
	return m_pos;
}

inline const TVector3& TGameObject::GetAngle( ) const
{
	return m_angle;
}

inline const TVector3& TGameObject::GetScale( ) const
{
	return m_scale;
}


}