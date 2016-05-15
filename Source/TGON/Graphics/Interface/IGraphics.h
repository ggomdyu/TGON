/*
* Author : Junho-Cha
* Date : 01/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../Core/TObject.h"
#include "../../Core/TNoncopyable.h"

namespace tgon
{


class TGON_API IGraphics : TNoncopyable
{
protected:
	IGraphics( ) {}
	virtual ~IGraphics( ) = 0 {}

public:
	virtual void BeginScene( ) = 0;
	virtual void EndScene( ) = 0;
};


}