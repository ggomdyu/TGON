/*
* 작성자 : 차준호
* 작성일 : 2016-01-10
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once

namespace tgon
{


class IGraphicsDeviceInterface
{
protected:
	IGraphicsDeviceInterface( ) {}
	virtual ~IGraphicsDeviceInterface( ) {}

public:
	virtual void BeginDraw( ) =0;
	virtual void EndDraw( ) = 0;
};


}