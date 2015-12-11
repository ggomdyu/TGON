//#include "stdafx.h"
#include "CommMessage.h"


tgon::CommMessage::CommMessage( const std::string & accepterType, unsigned int msgType, float delayTime ) :
	m_accepterType( accepterType ), m_msgType( msgType ), m_delayTime( delayTime )
{
}


tgon::CommMessage::~CommMessage( )
{
}