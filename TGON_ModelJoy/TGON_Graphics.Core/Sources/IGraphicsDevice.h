/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-10
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include "tgWindow.h"


namespace tgon
{

enum GraphicsDeviceProcessType
{
	kHardware,
	kSoftware,
};

struct GraphicsDeviceCreateParam
{
	virtual ~GraphicsDeviceCreateParam( ) = 0 {}
};

class IGraphicsDevice
{
public:
	IGraphicsDevice( )									{};
	virtual				~IGraphicsDevice( ) = 0		{};

	virtual bool		Setup( const GraphicsDeviceCreateParam* ) = 0;

	virtual void		BeginDisplay( ) =0;
	virtual void		EndDisplay( ) = 0;
};


}