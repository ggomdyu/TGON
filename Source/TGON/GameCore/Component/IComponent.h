/*
* Author : Cha Junho
* Date : 04/26/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Core/Platform/OSAL/PlatformInclude.h"
#include "../../Core/Object/Object.h"


namespace tgon
{


class TGON_API IComponent :
	public Object
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( IComponent, std::nullptr_t )

public:
	/*
		Ctor/Dtor
	*/
	explicit IComponent( class GameObject* owner );
	
	virtual ~IComponent( ) = 0;
	
	//virtual void Clone( ) = 0;


public:
	/*
		Commands
	*/
	virtual void Update( float tickTime ) = 0;

public:
	/*
		Sets
	*/
	void SetOwner( class GameObject* owner );
	
	/*
		Gets
	*/
	class GameObject* GetOwner( ) const;


private:
	class GameObject* m_owner;
};

inline void IComponent::SetOwner( GameObject* owner )
{
	m_owner = owner;
}

inline GameObject* IComponent::GetOwner( ) const
{
	return m_owner;
}


}