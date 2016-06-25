#pragma once
#include <tinyxml2/tinyxml2.h>


namespace tgon
{

using namespace tinyxml2;

class TXMLReader
{
	using _NodeRepoTy = std::vector<XMLNode*>;

public:
	explicit TXMLReader( const char* xmlPath );
	virtual ~TXMLReader( );

	using iterator = _NodeRepoTy::iterator;
	using const_iterator = _NodeRepoTy::const_iterator;

public:
	void LoadXML( const char* xmlPath );
	bool fail( ) const;

	iterator begin( );
	iterator end( );
	const_iterator begin( ) const;
	const_iterator end( ) const;

private:
	void RecursiveLoadImpl( XMLNode* );

private:
	bool m_isFailed;
	tinyxml2::XMLDocument m_xmlDocument;
	_NodeRepoTy m_readNodeRepo;
};

inline bool TXMLReader::fail( ) const
{
	return m_isFailed;
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