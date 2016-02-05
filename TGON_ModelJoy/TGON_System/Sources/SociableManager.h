/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-12-08
* ���� ���� :
* ���� ������ :
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