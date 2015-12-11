/*
* 작성자 : 차준호
* 작성일 : 2015-12-08
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "Singleton.h"

#include <string>
#include <unordered_map>

#include "ISociable.h"

/*
	WARNING! : DO NOT include windows header!!!!!!!
*/

namespace tgon {
	class SociableManager final
	{
		Implement_Singleton( SociableManager )
		typedef std::unordered_map<std::string, ISociable*> SociableRepo;

	public:
		SociableManager( );
		virtual ~SociableManager( );

	public:
		void				FrameMove( float elapsedTime );

		void				RegisterMember( _In_ ISociable* member )						{ m_sociableMap.insert( std::make_pair( member->GetName( ), member )); }
		void				DispatchMessage( _In_ const CommMessage& msg );

	private:
		SociableRepo	m_sociableMap;
	};
}