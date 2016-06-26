#pragma once
#include <tinyxml2/tinyxml2.h>


namespace tgon
{


class TXMLReader
{
	using _NodeRepoTy = std::vector<tinyxml2::XMLNode*>;

public:
	explicit TXMLReader( const char* xmlPath );
	virtual ~TXMLReader( );

	using iterator = _NodeRepoTy::iterator;
	using const_iterator = _NodeRepoTy::const_iterator;

public:
	void LoadXML( const char* xmlPath );
	bool Fail( ) const;
	tinyxml2::XMLError GetLastError( ) const;

	iterator begin( );
	iterator end( );
	const_iterator begin( ) const;
	const_iterator end( ) const;

private:
	void RecursiveLoadImpl( tinyxml2::XMLNode* );

private:
	bool m_isFailed;
	tinyxml2::XMLDocument m_xmlDocument;
	_NodeRepoTy m_readNodeRepo;
	tinyxml2::XMLError m_lastError;
};

inline bool TXMLReader::Fail( ) const
{
	return m_isFailed;
}

inline tinyxml2::XMLError tgon::TXMLReader::GetLastError( ) const
{
	return m_lastError;
}

inline TXMLReader::iterator TXMLReader::begin( )
{
	return m_readNodeRepo.begin( );
}

inline TXMLReader::iterator TXMLReader::end( )
{
	return m_readNodeRepo.end( );
}

inline TXMLReader::const_iterator tgon::TXMLReader::begin( ) const
{
	return m_readNodeRepo.begin( );
}

inline TXMLReader::const_iterator tgon::TXMLReader::end( ) const
{
	return m_readNodeRepo.end( );
}


}