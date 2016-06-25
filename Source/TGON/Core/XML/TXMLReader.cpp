#include "PrecompiledHeader.h"
#include "TXMLReader.h"



tgon::TXMLReader::TXMLReader( const char* xmlPath ) :
	m_isFailed( false )
{
	this->LoadXML( xmlPath );
}

tgon::TXMLReader::~TXMLReader( )
{
}

void tgon::TXMLReader::LoadXML( const char* xmlPath )
{
	if ( m_xmlDocument.LoadFile( xmlPath ) != XML_SUCCESS )
	{
		m_isFailed = true;
		return;
	}
	else
	{
		m_isFailed = false;
	}

	m_readNodeRepo.clear( );
	this->RecursiveLoadImpl( &m_xmlDocument );
}

void tgon::TXMLReader::RecursiveLoadImpl( tinyxml2::XMLNode* parent )
{
	if ( !parent )
	{
		return;
	}

	XMLNode* child = parent->FirstChild( );
	while ( child )
	{
		m_readNodeRepo.push_back( child );

		// Is the child has children?
		if ( child->FirstChild( ))
		{
			this->RecursiveLoadImpl( child );
		}

		child = child->NextSibling( );
	}
}