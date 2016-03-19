#include "stdafx.h"
#include "TinyXML2Util.h"

//void ErrorException( const XMLError xmlErr )
//{
//	tinyxml2::
//
//}


tinyxml2::XMLElement* FindElementRecursive( const std::string& nodeName, tinyxml2::XMLElement* parent )
{
	tinyxml2::XMLElement* sibling = parent->FirstChildElement( );
	tinyxml2::XMLElement* foundElem = nullptr;

	while ( sibling )
	{
		if ( sibling->Name( ) == nodeName )
		{
			return sibling;
		}
		else
		{
			foundElem = FindElementRecursive( nodeName, sibling );

			// found?
			if ( foundElem )
				return foundElem;

			// Otherwise, move to next sibling
			sibling = sibling->NextSiblingElement( );
		}
	}

	return nullptr;
}


tinyxml2::XMLElement* tinyxml2::FindSiblingElementFromParent( const std::string& nodeName, tinyxml2::XMLElement* parent )
{
	tinyxml2::XMLElement* sibling = parent->FirstChildElement( );

	while ( sibling )
	{
		if ( sibling->Name( ) == nodeName )
			return sibling;

		sibling = sibling->NextSiblingElement( );
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
	tinyxml2::XMLElement* root = document.RootElement( );

	if ( root->Name( ) == nodeName )
		return root;

	return FindElementRecursive( nodeName, root );
}