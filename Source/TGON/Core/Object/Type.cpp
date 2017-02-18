#include "PrecompiledHeader.h"
#include "Type.h"

#include "../Math/TMath.h"

namespace tgon
{

TypeInfo::TypeInfo(const std::string& name) noexcept :
    m_hashCode(Math::StringToHash(name.c_str(), name.length())),
    m_name(name)
{
}

TypeInfo::TypeInfo(const char* name, int length) noexcept :
    m_hashCode(Math::StringToHash(name, length)),
    m_name(name, length)
{
}

uint32_t TypeInfo::GetHashCode() const noexcept
{
    return m_hashCode;
}

const std::string& TypeInfo::GetName() const noexcept
{
    return m_name;
}

} /*namespace tgon*/