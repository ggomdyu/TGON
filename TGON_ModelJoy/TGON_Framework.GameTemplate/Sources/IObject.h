#pragma once
#include <iostream>
#include <map>

#include "GameTemplateTypes.h"
#include "IComponent.h"

namespace tgon {


class IComponent;
class IObject
{
public:
	IObject( );
	virtual ~IObject( );
	
	virtual void Initialize( )	{};
	virtual void FrameMove( float elapsedTime );

public:
	template <typename T> T* AddComponent( T* const pComponent );
	template <typename T> T* GetComponent( );

private:
	std::map<unsigned int, IComponent*> m_mapComponents;
};


}