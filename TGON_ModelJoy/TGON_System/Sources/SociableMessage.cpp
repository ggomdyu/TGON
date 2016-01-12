#include "stdafx.h"
#include "SociableMessage.h"

tgon::SociableMessage::SociableMessage( unsigned int accepterKey, unsigned int msgType, float delayTime ) :
	m_accepterKey( accepterKey ),
	m_msgType( msgType ),
	m_delayTime( delayTime )
{
}


tgon::SociableMessage::~SociableMessage( )
{
}