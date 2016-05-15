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
protected:
	struct _component_identifier {};


	/*
		Cons/Destructor
	*/
public:
	IComponent( );
	virtual ~IComponent( ) = 0;

	virtual void Update( float tickTime ) = 0;

	/*
		Sets
	*/
public:
	void SetOwner( TGameObject* const owner );


	/*
		Gets
	*/
public:
	TGameObject* GetOwner( ) const;
	virtual uint32_t GetComponentID( ) const = 0;


private:
	TGameObject* m_owner;
};

inline void IComponent::SetOwner( TGameObject* const owner )
{
	m_owner = owner;
}

inline TGameObject* IComponent::GetOwner( ) const
{
	return m_owner;
}


}