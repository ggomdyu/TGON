//#include "stdafx.h"
#include "SociableMessage.h"

tgon::SociableMessage::SociableMessage( uint32_t accepterKey, uint32_t msgType, float delayTime ) :
	m_accepterKey( accepterKey ), m_msgType( msgType ), m_delayTime( delayTime )
{
}


tgon::SociableMessage::~SociableMessage( )
{
}