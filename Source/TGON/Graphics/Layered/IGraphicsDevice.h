/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-10
* ���� ���� :
* ���� ������ :
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