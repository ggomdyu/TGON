/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-12-07
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include "ISociable.h"

namespace tgon {
	class ISystem : public ISociable
	{
	public:
		ISystem( uint32_t systemKey );
		virtual ~ISystem( );

		virtual void		Initialize( )										{};
		virtual void		FrameMove( float elapsedTime ) = 0;
	};
}