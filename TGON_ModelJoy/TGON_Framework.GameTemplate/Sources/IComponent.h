#pragma once
#include "GameTemplateTypes.h"
#include "IObject.h"


namespace tgon {


class IObject;
class IComponent
{
public:
	IComponent( );
	virtual ~IComponent( ) = 0;

	virtual void FrameMove( float elapsedTime ) = 0;

public:
	void SetOwner( IObject* pOwner );
	IObject* GetOwner( );

	template <typename T> static unsigned int GetComponentKey( );

private:
	IObject* m_pOwner;
};


}