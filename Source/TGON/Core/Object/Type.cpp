#include "PrecompiledHeader.h"
#include "Type.h"

#include "../Math/TMath.h"

namespace tgon
{

TypeInfo::TypeInfo( const std::string& name, const std::size_t length ) noexcept :
    m_hashCode( Math::StringToHash( name.c_str(), length )),
	m_name( name )
{
}

uint32_t TypeInfo::GetHashCode( ) const
{
    return m_hashCode;
}

const std::string& TypeInfo::GetName( ) const
{
    return m_name;
}

} /* namespace tgon */