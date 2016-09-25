#include "PrecompiledHeader.h"
#include "Type.h"

#include "../Math/Mathf.h"


namespace tgon
{


Type::Type( const std::string& name ) :
	m_hashCode( TMath::StringToHash( name.c_str( ))),
	m_name( name )
{
}

Type::~Type( )
{
}


} /*namespace tgon*/