/*
* 작성자 : 차준호
* 작성일 : 2015-12-08
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "Singleton.h"

#include <vector>
#include "SociableManager.h"
#include "SociableMessage.h"


namespace tgon {
	class MessageManager final
	{
		Implement_Singleton( MessageManager )

	public:
		void		FrameMove( );

	public:
		void		Broadcast( const SociableMessage& msg )		{ m_msgRepo.push_back( msg ); }

	private:
		MessageManager( );
		~MessageManager( );

	private:
		std::vector<SociableMessage>	m_msgRepo;
	};
}