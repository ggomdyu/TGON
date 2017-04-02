#include "PrecompiledHeader.h"
#include "TTypeInfo.h"

#include "../Hash/Hash.h"

namespace tgon
{

TTypeInfo::TTypeInfo(const std::string& name) noexcept :
    m_hashCode(Hash::StringToHash(name.c_str(), name.length())),
    m_name(name)
{
}

TTypeInfo::TTypeInfo(const char* name, int length) noexcept :
    m_hashCode(Hash::StringToHash(name, length)),
    m_name(name, length)
{
}

uint32_t TTypeInfo::GetHashCode() const noexcept
{
    return m_hashCode;
}

const std::string& TTypeInfo::GetName() const noexcept
{
    return m_name;
}

} /* namespace tgon */