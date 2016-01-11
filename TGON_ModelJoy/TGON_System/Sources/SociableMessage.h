#pragma once
#include <string>

namespace tgon {
/* Communicate */
	class SociableMessage
	{
	public:
		explicit SociableMessage( uint32_t accepterKey, uint32_t msgType, float delayTime = 0.0f );
		~SociableMessage( );
	
	public:
		void			SetDelayTime( float delayTime )		{ m_delayTime = delayTime; }
		float			GetDelayTime( ) const					{ return m_delayTime; }
	
		uint32_t		GetAccepterKey( ) const					{ return m_accepterKey; }
		uint32_t		GetMsgType( ) const						{ return m_msgType; }


	private:
		uint32_t		m_accepterKey;
		uint32_t		m_msgType;
		float			m_delayTime;
	};
}