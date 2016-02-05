#include "stdafx.h"
#include "TinyXML2Util.h"

//void ErrorException( const XMLError xmlErr )
//{
//	tinyxml2::
//
//}


tinyxml2::XMLElement* FindElementRecursive( const std::string& nodeName, tinyxml2::XMLElement* parent )
{
	tinyxml2::XMLElement* pSibling = parent->FirstChildElement( );
	tinyxml2::XMLElement* pFindElem = nullptr;

	while ( pSibling )
	{
		if ( pSibling->Name( ) == nodeName )
		{
			return pSibling;
		}
		else
		{
			pFindElem = FindElementRecursive( nodeName, pSibling );

			// found?
			if ( pFindElem )
				return pFindElem;

			// Otherwise, move to next sibling
			pSibling = pSibling->NextSiblingElement( );
		}
	}

	return nullptr;
}


tinyxml2::XMLElement* tinyxml2::FindSiblingElementFromParent( const std::string& nodeName, tinyxml2::XMLElement* parent )
{
	tinyxml2::XMLElement* pSibling = parent->FirstChildElement( );

	while ( pSibling )
	{
		if ( pSibling->Name( ) == nodeName )
			return pSibling;

		pSibling = pSibling->NextSiblingElement( );
	}

	return nullptr;
}


tinyxml2::XMLElement* tinyxml2::FindElementFromParent( const std::string& nodeName, tinyxml2::XMLElement* parent )
{
	if ( parent->Name( ) == nodeName )
		return parent;

	return FindElementRecursive( nodeName, parent );
}


tinyxml2::XMLElement* tinyxml2::FindElementFromRoot( const std::string& nodeName, tinyxml2::XMLDocument& document )
{
	tinyxml2::XMLElement* pRoot = document.RootElement( );

	if ( pRoot->Name( ) == nodeName )
		return pRoot;

	return FindElementRecursive( nodeName, pRoot );
}