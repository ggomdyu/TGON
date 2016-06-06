#include "PrecompiledHeader.h"
#include "TXMLAttribute.h"


tgon::TXMLAttribute::TXMLAttribute( 
	tinyxml2::XMLAttribute* xmlAttribute ) :
	m_xmlAttribute( xmlAttribute )
{
}

tgon::TXMLAttribute::~TXMLAttribute( )
{
}