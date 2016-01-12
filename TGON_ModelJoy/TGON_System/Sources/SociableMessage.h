#pragma once
#include <string>

namespace tgon {


/* Communicate */
class SociableMessage
{
public:
	explicit SociableMessage( unsigned int accepterKey, unsigned int msgType, float delayTime = 0.0f );
	~SociableMessage( );
	
public:
	void			SetDelayTime( float delayTime )		{ m_delayTime = delayTime; }
	float			GetDelayTime( ) const					{ return m_delayTime; }
	
	unsigned int		GetAccepterKey( ) const					{ return m_accepterKey; }
	unsigned int		GetMsgType( ) const						{ return m_msgType; }


private:
	unsigned int		m_accepterKey;
	unsigned int		m_msgType;
	float			m_delayTime;
};


}