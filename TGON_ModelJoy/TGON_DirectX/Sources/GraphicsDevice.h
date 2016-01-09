/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-08
* ���� ���� : 
* ���� ������ : 
*/

// Happy new year 2016!!

#pragma once
#include "GraphicsDeviceType.h"
#include <Pattern\Singleton.h>


class IGraphicsDeviceImpl;
class GraphicsDevice : public IGraphicsDeviceImpl
{
public:
	Declare_Static_Singleton( GraphicsDevice )


	virtual bool		Setup( int width, int height, GraphicsDeviceType gdt ) override		{ device->Setup( width, height, gdt ); }
	virtual void		Display( )	 override																	{ device->Display( ); }

private:
						GraphicsDevice( );
	virtual				~GraphicsDevice( );

	void				operator delete ( void* arg )		{ std::free( arg ); }

private:
	IGraphicsDeviceImpl* device;
};


class IGraphicsDeviceImpl
{
public:
						IGraphicsDeviceImpl( ) {};
	virtual				~IGraphicsDeviceImpl( ) = 0 {};

	virtual bool		Setup( int width, int height, GraphicsDeviceType gdt ) = 0;
	virtual void		Display( ) = 0;
};