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
		ISystem( );
		virtual ~ISystem( );

		virtual void		Initialize( ) = 0;
		virtual void		FrameMove( float elapsedTime )		{}
		virtual void		FrameMove( )							{}
	};
}