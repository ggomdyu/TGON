/*
* Author : Junho-Cha
* Date : 01/28/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <tinyxml2_wchar_t.h>

namespace tgon
{
	
	/* 
		Breadth node search
	*/
	tinyxml2::XMLElement* FindElementFromParent( 
		const wchar_t* nodeName,
		tinyxml2::XMLElement* parentNode
	);

//struct TXMLNode
//{
//public:
//	TXMLNode( ) {};
//	TXMLNode( tinyxml2::XMLNode* const node ) :
//		m_node( node ) {}
//
//
//private:
//	tinyxml2::XMLNode* m_node;
//};
//
//
//class TXMLDocument : private tinyxml2::TiXMLDocument
//{
//public:
//	TXMLDocument( )
//	{
//	}
//	explicit TXMLDocument( const wchar_t* const xmlPath )
//	{
//		this->LoadXML( xmlPath );
//	}
//	~TXMLDocument( )
//	{
//	}
//
//public:
//	void LoadXML( const wchar_t* const xmlPath );
//
//	/*
//		Gets
//	*/
//	TXMLNode GetRoot( )
//	{
//		return this->RootElement( );
//	}
//
//private:
//};
//
//
//inline void TXMLDocument::LoadXML( const wchar_t* xmlPath )
//{
//	this->LoadFile( xmlPath );
//}
}