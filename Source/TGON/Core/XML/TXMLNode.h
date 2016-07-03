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


class TXMLNode
{
public:
	TXMLNode( tinyxml2::XMLNode* xmlNode );
	virtual ~TXMLNode( );

	void SetValue( const wchar_t* val ) const;
	const wchar_t* GetValue( ) const;

	TXMLNode GetNextSibling( );

private:
	tinyxml2::XMLNode* m_xmlNode;
};

inline TXMLNode tgon::TXMLNode::GetNextSibling( )
{
	return m_xmlNode->NextSibling( );
}

inline void TXMLNode::SetValue( 
	const wchar_t* val ) const
{
	m_xmlNode->SetValue( val );
}

inline const wchar_t* TXMLNode::GetValue( ) const
{
	return m_xmlNode->Value( );
}


}