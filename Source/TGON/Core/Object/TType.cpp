#include "PrecompiledHeader.h"
#include "TType.h"

#include "../Math/TMath.h"


tgon::TType::TType( const char* name ) :
	m_hashCode( TMath::GenerateHash( name )),
	m_name( name )
{
}

tgon::TType::~TType( )
{
}
