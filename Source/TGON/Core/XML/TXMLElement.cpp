#include "PrecompiledHeader.h"
#include "TXMLElement.h"


tgon::TXMLElement::TXMLElement( 
	tinyxml2::XMLElement* xmlElement ) :
	TXMLNode( xmlElement )
{
}

tgon::TXMLElement::~TXMLElement( )
{
}


//void ErrorException( const XMLError xmlErr )
//{
//	tinyxml2::
//
//}


//tinyxml2::XMLElement* FindElementRecursive(
//	const std::string& nodeName,
//	tinyxml2::XMLElement* const parent )
//{
//	tinyxml2::XMLElement* sibling = parent->FirstChildElement( );
//	tinyxml2::XMLElement* foundElem = nullptr;
//
//	while ( sibling )
//	{
//		if ( sibling->Name( ) == nodeName )
//		{
//			return sibling;
//		}
//		else
//		{
//			foundElem = FindElementRecursive( nodeName, sibling );
//
//			// found?
//			if ( foundElem )
//			{
//				return foundElem;
//			}
//
//			// Otherwise, move to next sibling
//			sibling = sibling->NextSiblingElement( );
//		}
//	}
//
//	return nullptr;
//}


//tinyxml2::XMLElement* tgon::FindElementFromParent(
//		const char* const nodeName,
//		const tinyxml2::XMLNode* const parentNode )
//{
//
//	return nullptr;
//}
//
//tgon::XMLElement* tgon::FindElementFromParent(
//	const wchar_t* nodeName,
//	XMLElement* parentNode )
//{
//	XMLElement* sibling = parentNode->FirstChildElement( );
//
//	while ( sibling )
//	{
//		if ( !std::wcscmp( sibling->Name(), nodeName ))
//		{
//			return sibling;
//		}
//
//		sibling = sibling->NextSiblingElement( );
//	}
//
//	return nullptr;
//}
//


//tinyxml2::XMLElement* tgon::FindElementFromParent(
//	const std::string& nodeName,
//	tinyxml2::XMLElement* const parent )
//{
//	if ( parent->Name( ) == nodeName )
//	{
//		return parent;
//	}
//
//	return FindElementRecursive( nodeName, parent );
//}
//
//
//tinyxml2::XMLElement* tgon::FindElementFromRoot(
//	const std::string& nodeName,
//	tinyxml2::XMLDocument& document )
//{
//	tinyxml2::XMLElement* root = document.RootElement( );
//
//	if ( root->Name( ) == nodeName )
//	{
//		return root;
//	}
//
//	return FindElementRecursive( nodeName, root );
//}

