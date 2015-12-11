/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <string>
#include "MsgManager.h"

namespace tgon {
	enum SociableEnum
	{
		Social_Unknown,
		Social_System,
		Social_Object,
		Social_Component,
	};

	class ISociable
	{
	public:
		ISociable( const SociableEnum sociableType );
		ISociable( _In_ const std::string& name, const SociableEnum sociableType );
		ISociable( _In_ std::string&& name, const SociableEnum sociableType );
		virtual ~ISociable( );

	public:
		virtual void					RecvMessage( _In_ const CommMessage& msg ) = 0;

		void							SetName( _In_ const std::string& name )	{ m_name = name; }
		void							SetName( _In_ std::string&& name )			{ m_name = std::move( name ); }
		const std::string&			GetName( ) const									{ return m_name; }

	private:
		const SociableEnum		m_sociableType;
		std::string					m_name;
	};
}