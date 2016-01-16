/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-08
* ���� ���� : ����ȣ
* ���� ������ : 2016-01-10
*/

// Happy new year 2016!!

#pragma once
#include "IGraphicsDeviceImpl.h"
#include <memory>

namespace tgon
{


class GraphicsDevice
{

public:
	explicit GraphicsDevice( IGraphicsDeviceImpl* pImpl ) :
		m_device( pImpl )		{}
	~GraphicsDevice( )	{};

	bool		Setup( const GraphicsDeviceCreateParam* gdp )		{ return m_device->Setup( gdp ); }
	void		Display( )															{ m_device->Display( ); }

private:
	std::shared_ptr<IGraphicsDeviceImpl> m_device;		// �и��ϰ��� abstract ��ü�� ��ó�� �ӿ��� �ζ��̴��ϴ°� �ȵ� �ذ�å�� �ʿ���
};


}