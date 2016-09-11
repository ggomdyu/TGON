#include "PrecompiledHeader.h"
#include "TXMLReader.h"


tgon::TXMLReader::TXMLReader( const char* xmlPath ) :
	m_isFailed( false ),
	m_lastError( tinyxml2::XMLError::XML_SUCCESS )
{
	this->LoadXML( xmlPath );
}

tgon::TXMLReader::~TXMLReader( )
{
}

void tgon::TXMLReader::LoadXML( const char* xmlPath )
{
	m_lastError = m_xmlDocument.LoadFile( xmlPath );
	if ( m_lastError != tinyxml2::XML_SUCCESS )
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

	tinyxml2::XMLNode* child = parent->FirstChild( );
	while ( child )
	{
		m_readNodeRepo.push_back( child );

		// Is node has children?
		if ( child->FirstChild( ))
		{
			this->RecursiveLoadImpl( child );
		}

		child = child->NextSibling( );
	}
}