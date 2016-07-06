#pragma once
#include "TXMLNode.h"


namespace tgon
{


class TXMLAttribute
{
public:
	TXMLAttribute( tinyxml2::XMLAttribute* xmlAttribute );
	virtual ~TXMLAttribute( );

private:
	tinyxml2::XMLAttribute* m_xmlAttribute;
};


}
