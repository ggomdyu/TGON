/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-12-08
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include <Pattern\Singleton.h>

#include <string>
#include <unordered_map>

#include "ISociable.h"

/*
	WARNING! : DO NOT include windows header!!!!!!!
*/

namespace tgon {
	class SociableManager final
	{
		typedef std::unordered_map<uint32_t, ISociable*> SociableRepo;

	public:
		Declare_Static_Singleton( SociableManager )

	public:
		void		FrameMove( float elapsedTime );

	public:
		void		RegisterMember( _In_ ISociable* member );
		void		DispatchMessage( _In_ const SociableMessage& msg );

	private:
		SociableManager( );
		~SociableManager( );


	private:
		SociableRepo	m_sociableMap;
	};
}