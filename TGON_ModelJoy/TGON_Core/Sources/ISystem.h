/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
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