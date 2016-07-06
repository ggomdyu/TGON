/*
* Author : Junho-Cha
* Date : 04/26/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IComponent
{
public:
	/*
		Constructor
	*/
	IComponent( class TGameObject* owner );
	
	/*
		Destructor
	*/
	virtual ~IComponent( ) = 0;

public:
	/*
		Commands
	*/
	//virtual void Clone( ) = 0;
	
	virtual void Update( float tickTime ) = 0;

public:
	/*
		Sets
	*/
	// Set this component's owner.
	void SetOwner( class TGameObject* owner );
	
	/*
		Gets
	*/
	// Return component's owner.
	class TGameObject* GetOwner( ) const;


private:
	class TGameObject* m_owner;
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