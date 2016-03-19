#pragma once
#include <iostream>
#include <map>

#include "IComponent.h"

namespace tgon {


class IComponent;
class IObject
{
public:
	IObject( );
	virtual ~IObject( );
	
	virtual void Setup( ) {};
	virtual void Run( float tickTime );

public:
	template <typename T> T* AddComponent( T* component );
	template <typename T> T* GetComponent( );

private:
	std::map<uint32_t, IComponent*> m_components;
};


}