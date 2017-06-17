#include "PrecompiledHeader.h"
#include "TypeInfo.h"

#include "Core/Hash/Hash.h"

namespace tgon
{
namespace object
{

TypeInfo::TypeInfo(const std::string& name) noexcept :
    m_hashCode(Hash::StringToHash(name.c_str(), name.length())),
    m_typeName(name)
{
}

TypeInfo::TypeInfo(const char* name, std::size_t length) noexcept :
    m_hashCode(Hash::StringToHash(name, length)),
    m_typeName(name, length)
{
}

std::size_t TypeInfo::GetHashCode() const noexcept
{
    return m_hashCode;
}

const std::string& TypeInfo::GetTypeName() const noexcept
{
    return m_typeName;
}

} /* namespace object */
} /* namespace tgon */
