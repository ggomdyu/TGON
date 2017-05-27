#include "PrecompiledHeader.h"
#include "TTypeInfo.h"

#include "Core/Hash/Hash.h"

namespace tgon {
namespace object {

TTypeInfo::TTypeInfo(const std::string& name) noexcept :
    m_hashCode(Hash::StringToHash(name.c_str(), name.length())),
    m_typeName(name)
{
}

TTypeInfo::TTypeInfo(const char* name, std::size_t length) noexcept :
    m_hashCode(Hash::StringToHash(name, length)),
    m_typeName(name, length)
{
}

std::size_t TTypeInfo::GetHashCode() const noexcept
{
    return m_hashCode;
}

const std::string& TTypeInfo::GetTypeName() const noexcept
{
    return m_typeName;
}

} /* namespace object */
} /* namespace tgon */