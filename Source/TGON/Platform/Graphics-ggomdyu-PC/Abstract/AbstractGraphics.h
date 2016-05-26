/*
* Author : Junho-Cha
* Date : 01/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../TGraphicsType.h"
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IGraphics : 
	boost::noncopyable
{
public:
	virtual void Clear( ) = 0;
	virtual void Begin( ) = 0;
	virtual void End( ) = 0;
	virtual void Present( ) = 0;

	virtual void Draw( PrimitiveType primitiveType,
					   int32_t startVertex,
					   int32_t primitiveCount ) = 0;

	virtual void Draw( PrimitiveType primitiveType,
					   int32_t indexStart,
					   int32_t indexCount, 
					   int32_t minVertex,
					   int32_t vertexCount ) = 0;
protected:
	IGraphics( ) {}
	virtual ~IGraphics( ) = 0 {}
};


}