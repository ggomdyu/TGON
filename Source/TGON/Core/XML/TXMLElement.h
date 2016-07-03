/*
* Author : Junho-Cha
* Date : 01/28/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TXMLNode.h"


namespace tgon
{


class TXMLElement :
	public TXMLNode
{
public:
	TXMLElement( tinyxml2::XMLElement* xmlElement );
	virtual ~TXMLElement( );
};


}