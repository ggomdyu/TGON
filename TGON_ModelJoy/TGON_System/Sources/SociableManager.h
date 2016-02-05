/*
* 작성자 : 차준호
* 작성일 : 2015-12-08
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <Pattern\Singleton.h>

#include <unordered_map>
#include "ISociable.h"


namespace tgon {
	class SociableManager final
	{
		typedef std::unordered_map<unsigned int, ISociable*> SociableRepo;

	public:
		DECLARE_STATIC_SINGLETON( SociableManager )

	public:
		void FrameMove( float elapsedTime );

	public:
		void RegisterMember( _In_ ISociable* member );
		void DispatchMessage( const SociableMessage& msg );

	private:
		SociableManager( );
		~SociableManager( );


	private:
		SociableRepo m_sociableMap;
	};
}