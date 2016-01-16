/*
* 작성자 : 차준호
* 작성일 : 2016-01-08
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-10
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
	std::shared_ptr<IGraphicsDeviceImpl> m_device;		// 분리하고보니 abstract 객체인 것처럼 속여서 인라이닝하는게 안됨 해결책이 필요함
};


}