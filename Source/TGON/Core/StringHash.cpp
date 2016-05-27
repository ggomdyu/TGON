#include "PrecompiledHeader.h"
#include "StringHash.h"

#include "Math/TMath.h"


tgon::StringHash::StringHash( const char* str ) :
	m_hashCode( TMath::GenerateHash( str ))
{
}

tgon::StringHash::~StringHash( )
{
}