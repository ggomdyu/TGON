#pragma once
#include "TXMLNode.h"


namespace tgon
{


class TXMLText :
	public TXMLNode
{
public:
	TXMLText( tinyxml2::XMLText* xmlText );
	virtual ~TXMLText( );
};


}