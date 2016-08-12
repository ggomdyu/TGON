#include "PrecompiledHeader.h"
#include "TType.h"

#include "../Math/TMath.h"


tgon::TType::TType( const std::string& name ):
	m_hashCode( TMath::GenerateHash( name.c_str( ))),
	m_name( name )
{
}

tgon::TType::~TType( )
{
}
