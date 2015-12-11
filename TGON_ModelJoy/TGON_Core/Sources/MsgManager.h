/*
* 작성자 : 차준호
* 작성일 : 2015-12-08
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "Singleton.h"

#include <vector>
#include "CommMessage.h"


namespace tgon {
	class MsgManager final
	{
		Implement_Singleton( MsgManager )

	public:
		void				FrameMove( );
		void				Request( const CommMessage& msg )		{ m_msgRepo.push_back( msg ); }

	private:
		MsgManager( );
		~MsgManager( );

	private:
		std::vector<CommMessage>	m_msgRepo;
	};
}