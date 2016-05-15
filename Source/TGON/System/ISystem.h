#pragma once
#include "../Core/TObject.h"
#include "../Core/TNoncopyable.h"


namespace tgon
{


class TGON_API ISystem :
	public TObject,
	private TNoncopyable
{
public:
	TGON_OBJECT( ISystem, TObject )

public:
	virtual void Update( float tickTime ) = 0;	

protected:
	ISystem( ) {};
	virtual ~ISystem( ) = 0 {};
};


}