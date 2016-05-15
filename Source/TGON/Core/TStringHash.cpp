#include "PrecompiledHeader.h"
#include "TStringHash.h"

#include <Math/TMath.h>

tgon::TStringHash::TStringHash( const char* str ) :
	m_hash( TMath::GenerateHash( str ))
{
}

tgon::TStringHash::~TStringHash( )
{
}