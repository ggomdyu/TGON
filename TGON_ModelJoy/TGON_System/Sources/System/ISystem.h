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
		ISystem( unsigned int key );
		virtual ~ISystem( );

		virtual void Setup( )	{};
		virtual void FrameMove( float elapsedTime ) = 0;
	};
}