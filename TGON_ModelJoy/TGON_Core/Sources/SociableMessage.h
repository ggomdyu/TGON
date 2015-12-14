#pragma once
#include <string>

namespace tgon {
/* Communicate */
	class SociableMessage
	{
	public:
		explicit SociableMessage( const std::string& accepterName, unsigned int msgType, float delayTime = 0.0f );
		~SociableMessage( );
	
	public:
		void				SetDelayTime( float delayTime )		{ m_delayTime = delayTime; }
		float				GetDelayTime( ) const					{ return m_delayTime; }
	
		std::string			GetAccepterName( ) const				{ return m_accepterName; }
		unsigned int		GetMsgType( ) const					{ return m_msgType; }


	private:
		std::string			m_accepterName;
		unsigned int		m_msgType;
		float				m_delayTime;
	};
}