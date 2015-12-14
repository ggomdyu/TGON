//#include "stdafx.h"
#include "SociableMessage.h"

tgon::SociableMessage::SociableMessage( const std::string& accepterName, unsigned int msgType, float delayTime ) :
	m_accepterName( accepterName ), m_msgType( msgType ), m_delayTime( delayTime )
{
}


tgon::SociableMessage::~SociableMessage( )
{
}