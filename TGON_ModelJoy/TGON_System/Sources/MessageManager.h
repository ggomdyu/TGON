/*
* 작성자 : 차준호
* 작성일 : 2015-12-08
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <Pattern\Singleton.h>

#include <vector>
#include "SociableManager.h"
#include "SociableMessage.h"


namespace tgon {
	class MessageManager final
	{
	public:
		DECLARE_STATIC_SINGLETON( MessageManager )

	public:
		void		FrameMove( float elapsedTime );
		void		Broadcast( const SociableMessage& msg )		{ m_msgRepo.push_back( msg ); }

	private:
		MessageManager( );
		~MessageManager( );

	private:
		std::vector<SociableMessage>	m_msgRepo;
	};
}