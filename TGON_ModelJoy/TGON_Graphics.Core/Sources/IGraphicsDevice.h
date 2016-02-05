/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-10
* ���� ���� :
* ���� ������ :
*/

#pragma once

namespace tgon
{

enum GraphicsDeviceProcessType
{
	kHardware,
	kSoftware,
};

struct GraphicsDeviceCreateParam
{
	bool	isFullWindow;
	int		resolution_x;
	int		resoultion_y;

	GraphicsDeviceProcessType		gdpt;
};

class IGraphicsDevice
{
public:
	IGraphicsDevice( )		{};
	virtual		~IGraphicsDevice( ) = 0		{};

	virtual void		BeginDisplay( ) =0;
	virtual void		EndDisplay( ) = 0;
};
}