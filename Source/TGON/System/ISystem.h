#pragma once
#include <boost/noncopyable.hpp>
#include "../Core/TObject.h"


namespace tgon
{


class TGON_API ISystem :
	public TObject,
	private boost::noncopyable
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