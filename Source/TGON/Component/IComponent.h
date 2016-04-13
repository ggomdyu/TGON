/*
* Author : Junho-Cha
* Date : 2015-04-26
* Latest author :
* Latest date :
*/


#pragma once
#include <stdint.h>
#include "../Object/TGameObject.h"


namespace tgon
{


class TGameObject;
class IComponent
{
public:
	IComponent( ) : m_owner( nullptr ) {};
	virtual ~IComponent( ) = 0 {};

	virtual void Update( float elapsedTime ) = 0;

public:
	void SetOwner( TGameObject* const owner );
	TGameObject* GetOwner( ) const;

	template <typename T>
	static uint32_t GetIdentifier( );

private:
	TGameObject* m_owner;
};


}

void tgon::IComponent::SetOwner( TGameObject* const owner )
{
	m_owner = owner;
}

inline TGameObject* tgon::IComponent::GetOwner( )
{
	return m_owner;
}

template<typename T>
inline uint32_t tgon::IComponent::GetIdentifier( )
{
	static const auto keyCode( typeid(T).hash_code( ));
	return keyCode;
}