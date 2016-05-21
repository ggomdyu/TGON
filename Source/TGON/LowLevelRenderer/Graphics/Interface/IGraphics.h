/*
* Author : Junho-Cha
* Date : 01/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../../Platform/Config/BuildOption.h"

namespace tgon
{


class TGON_API IGraphics : 
	private boost::noncopyable
{
public:
	virtual void BeginScene( ) = 0;
	virtual void EndScene( ) = 0;

protected:
	IGraphics( ) {}
	virtual ~IGraphics( ) = 0 {}
};


}