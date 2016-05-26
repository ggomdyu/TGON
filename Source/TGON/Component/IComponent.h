/*
* Author : Junho-Cha
* Date : 04/26/2015
* Latest author :
* Latest date :
*/

#pragma once
#include <stdint.h>
#include "../Core/TGameObject.h"



namespace tgon
{


class TGameObject;
class IComponent
{
public:
	virtual void Update( float tickTime ) = 0;


public:
	/*
		Set/Gets
	*/
	void SetOwner( TGameObject* owner );
	TGameObject* GetOwner( ) const;


	/*
		Cons/Destructor
	*/
public:
	IComponent( );
	virtual ~IComponent( ) = 0;


private:
	TGameObject* m_owner;
};

inline void IComponent::SetOwner( TGameObject* owner )
{
	m_owner = owner;
}

inline TGameObject* IComponent::GetOwner( ) const
{
	return m_owner;
}


}