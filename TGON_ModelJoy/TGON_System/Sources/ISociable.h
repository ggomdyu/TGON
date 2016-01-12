/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "SociableMessage.h"

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
		ISociable( unsigned int key, SociableEnum sociableType );
		virtual ~ISociable( );

		virtual void	RecvMessage( _In_ const SociableMessage& msg ) = 0;
		unsigned int		GetKey( ) const						{ return m_key; }

	private:
		void			SetKey( unsigned int key )			{ m_key = key; }

	private:
		const SociableEnum	m_sociableType;
		unsigned int					m_key;
	};
}