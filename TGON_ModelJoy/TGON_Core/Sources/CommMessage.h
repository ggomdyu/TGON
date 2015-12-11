#pragma once
#include <string>

namespace tgon {
/* Communicate */
	class CommMessage
	{
	public:
		explicit CommMessage( const std::string& accepterType, unsigned int msgType, float delayTime = 0.0f );
		~CommMessage( );
	

		void					SetDelayTime( float delayTime )		{ m_delayTime = delayTime; }
		float					GetDelayTime( ) const					{ return m_delayTime; }
	
		std::string			GetAccepterType( ) const				{ return m_accepterType; }
		unsigned int		GetMsgType( ) const						{ return m_msgType; }


	private:
		std::string			m_accepterType;
		unsigned int		m_msgType;
		float					m_delayTime;
	};
}